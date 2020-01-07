#include "cam_application.hpp"
#include <vanetza/btp/ports.hpp>
// #include <vanetza/asn1/its/InformationQuality.h>
// #include <vanetza/asn1/its/CauseCodeType.h>
#include <vanetza/asn1/its/CollisionRiskSubCauseCode.h>
#include <vanetza/asn1/cam.hpp>
#include <vanetza/asn1/denm.hpp>
#include <vanetza/asn1/packet_visitor.hpp>
#include <vanetza/facilities/cam_functions.hpp>
// #include <vanetza/geonet/indication_context.hpp>
// #include <vanetza/geonet/header_variant.hpp>
// #include <vanetza/net/ethernet_header.hpp>
#include <vanetza/geonet/serialization_buffer.hpp>
#include <boost/units/cmath.hpp>
#include <boost/units/systems/si/prefixes.hpp>
#include <chrono>
#include <exception>
#include <functional>
#include <iostream>

// This is rather simple application that sends CAMs in a regular interval.
using namespace vanetza;
using namespace vanetza::facilities;
using namespace std::chrono;

auto microdegree = vanetza::units::degree * boost::units::si::micro;

template<typename T, typename U>
long round(const boost::units::quantity<T>& q, const U& u)
{
	boost::units::quantity<U> v { q };
	return std::round(v.value());
}

CamApplication::CamApplication(PositionProvider& positioning, const Runtime& rt, boost::asio::steady_timer& timer, milliseconds cam_interval)
    : positioning_(positioning), runtime_(rt), cam_interval_(cam_interval), timer_(timer)
{
    schedule_timer();
}

CamApplication::PortType CamApplication::port()
{
    return btp::ports::CAM;
}

void CamApplication::indicate(const DataIndication& indication, UpPacketPtr packet)
{
    vanetza::CohesivePacket* p = boost::get<vanetza::CohesivePacket>(packet.get());

    /* 
    auto linkBufferRange = create_byte_view(*p, OsiLayer::Link, OsiLayer::Link);
    EthernetHeader linkBuffer = vanetza::decode_ethernet_header(linkBufferRange.begin(), linkBufferRange.end());
    vanetza::geonet::LinkLayer macAddr;
    macAddr.destination = linkBuffer.destination;
    macAddr.sender = linkBuffer.source;
    vanetza::geonet::IndicationContextDeserialize networkDeserialize(std::move(packet), *p, macAddr);
    boost::optional<vanetza::geonet::HeaderConstRefVariant> extHeader = networkDeserialize.parse_extended(vanetza::geonet::HeaderType::TSB_Single_Hop);
    vanetza::geonet::ShbHeader shbHeader;
    if (extHeader) {
        shbHeader = boost::get<const vanetza::geonet::ShbHeader>(*extHeader);
    } 
    packet = networkDeserialize.finish(); 
    */
    
    auto networkBufferRange = create_byte_view(*p, OsiLayer::Network, OsiLayer::Network);
    ByteBuffer BasicHeaderBuffer(networkBufferRange.begin(), networkBufferRange.end());
    vanetza::geonet::BasicHeader basicHeader;
    vanetza::geonet::deserialize_from_buffer(basicHeader, BasicHeaderBuffer);
    if (basicHeader.next_header == geonet::NextHeaderBasic::Any) {

    } else if (basicHeader.next_header == geonet::NextHeaderBasic::Common) {
        ByteBuffer CommonHeaderBuffer(networkBufferRange.begin() + 
            geonet::BasicHeader::length_bytes, networkBufferRange.end());   
        vanetza::geonet::CommonHeader commonHeader;
        vanetza::geonet::deserialize_from_buffer(commonHeader, CommonHeaderBuffer);    
        if (commonHeader.header_type == geonet::HeaderType::TSB_Single_Hop) {
            ByteBuffer GnPacketBuffer(networkBufferRange.begin() + 
                geonet::BasicHeader::length_bytes + geonet::CommonHeader::length_bytes, 
                networkBufferRange.end());   
            vanetza::geonet::ShbHeader tsbHeader;
            vanetza::geonet::deserialize_from_buffer(tsbHeader, GnPacketBuffer); 

            std::cout << "GN Location " << tsbHeader.source_position.gn_addr.mid() << std::endl;
            std::cout << "GN Station Type " << (int)tsbHeader.source_position.gn_addr.station_type() << std::endl;
            std::cout << "GN is_manually_configured " << tsbHeader.source_position.gn_addr.is_manually_configured() << std::endl;
            std::cout << "GN Timestamp " << tsbHeader.source_position.timestamp.raw() << std::endl; 

        } else { // if commonHeader.header_type == "other types of header"

        }

        // auto transportBufferRange = create_byte_view(*p, OsiLayer::Transport, OsiLayer::Transport);
        // ByteBuffer transportBuffer(transportBufferRange.begin(), transportBufferRange.end());
        // CohesivePacket btppacket(transportBuffer, OsiLayer::Transport);
        if (commonHeader.next_header == geonet::NextHeaderCommon::BTP_A) {
            vanetza::btp::HeaderA btpHeader;
            btpHeader = vanetza::btp::parse_btp_a(*p);
            std::cout << "BTP Destination Port " << btpHeader.destination_port << std::endl;
            std::cout << "BTP Source Port " << btpHeader.source_port << std::endl;
        } else if (commonHeader.next_header == geonet::NextHeaderCommon::BTP_B) {
            vanetza::btp::HeaderB btpHeader;
            btpHeader = vanetza::btp::parse_btp_b(*p);
            std::cout << "BTP Destination Port " << btpHeader.destination_port << std::endl;
            std::cout << "BTP Destination Port Info " << btpHeader.destination_port_info << std::endl;
        } else {

        }


    } else { // if (basicHeader.next_header == geonet::NextHeaderBasic::Secured)
  
    }

    vanetza::asn1::Cam camMessage; 
    auto applicationBufferRange = create_byte_view(*p, OsiLayer::Session, OsiLayer::Application);
    bool result_decodeCAM = camMessage.decode(applicationBufferRange.begin(), applicationBufferRange.end());

    std::cout << "CAM Message Type " << e_ItsPduHeader__messageID(camMessage->header.messageID) << std::endl;
    std::cout << "CAM Station ID " << camMessage->header.stationID << std::endl;
    std::cout << "CAM Station Type " << e_StationType(camMessage->cam.camParameters.basicContainer.stationType) << std::endl;
    std::cout << "CAM Generation Delta Time " << camMessage->cam.generationDeltaTime << std::endl;

}

void CamApplication::schedule_timer()
{
    timer_.expires_from_now(cam_interval_);
    timer_.async_wait(std::bind(&CamApplication::on_timer, this, std::placeholders::_1));
}

void CamApplication::on_timer(const boost::system::error_code& ec)
{
    if (ec == boost::asio::error::operation_aborted) {
        return;
    }

    // vanetza::asn1::Cam message;
    vanetza::asn1::Denm message;

    ItsPduHeader_t& header = message->header;
    header.protocolVersion = 2;
    // header.messageID = ItsPduHeader__messageID_cam;
    header.messageID = ItsPduHeader__messageID_denm;
    header.stationID = 4; // some dummy value
    
    auto position = positioning_.position_fix();
    std::chrono::time_point<vanetza::Clock> tp2004 = vanetza::Clock::at("2004-01-01 00:00:00");
    const auto time_now = duration_cast<milliseconds>(runtime_.now().time_since_epoch());
    const auto time_2004 = duration_cast<milliseconds>(tp2004.time_since_epoch());

    //-------------------------CAM-------------------------//

    // uint16_t gen_delta_time = time_now.count() - time_2004.count();
    // CoopAwareness_t& cam = message->cam;
    // cam.generationDeltaTime = gen_delta_time * GenerationDeltaTime_oneMilliSec;
    
    // // std::cout << position.confidence << std::endl;
    // if (!position.confidence) {
    //     schedule_timer();

    //     std::cerr << "Skipping CAM, because no good position is available, yet." << std::endl;

    //     return;
    // }

    // BasicContainer_t& basic = cam.camParameters.basicContainer;
    // basic.stationType = StationType_pedestrian;
    // basic.referencePosition.longitude = round(position.longitude, microdegree) * Longitude_oneMicrodegreeEast;
    // basic.referencePosition.latitude = round(position.latitude, microdegree) * Latitude_oneMicrodegreeNorth;
    // basic.referencePosition.positionConfidenceEllipse.semiMajorOrientation = HeadingValue_unavailable;
    // basic.referencePosition.positionConfidenceEllipse.semiMajorConfidence = SemiAxisLength_unavailable;
    // basic.referencePosition.positionConfidenceEllipse.semiMinorConfidence = SemiAxisLength_unavailable;
    
    // if (position.altitude) {
    //     basic.referencePosition.altitude.altitudeValue = to_altitude_value(position.altitude->value());
    //     basic.referencePosition.altitude.altitudeConfidence = to_altitude_confidence(position.altitude->confidence());
    // } else {
    //     basic.referencePosition.altitude.altitudeValue = AltitudeValue_unavailable;
    //     basic.referencePosition.altitude.altitudeConfidence = AltitudeConfidence_unavailable;
    // }

    // cam.camParameters.highFrequencyContainer.present = HighFrequencyContainer_PR_basicVehicleContainerHighFrequency;

    // BasicVehicleContainerHighFrequency& bvc = cam.camParameters.highFrequencyContainer.choice.basicVehicleContainerHighFrequency;
    // bvc.heading.headingValue = 0;
    // bvc.heading.headingConfidence = HeadingConfidence_equalOrWithinOneDegree;

    // bvc.speed.speedValue = 0;
    // bvc.speed.speedConfidence = SpeedConfidence_equalOrWithinOneCentimeterPerSec;

    // bvc.driveDirection = DriveDirection_forward;
    // bvc.longitudinalAcceleration.longitudinalAccelerationValue = LongitudinalAccelerationValue_unavailable;

    // bvc.vehicleLength.vehicleLengthValue = VehicleLengthValue_unavailable;
    // bvc.vehicleLength.vehicleLengthConfidenceIndication = VehicleLengthConfidenceIndication_noTrailerPresent;
    // bvc.vehicleWidth = VehicleWidth_unavailable;

    // bvc.curvature.curvatureValue = 0;
    // bvc.curvature.curvatureConfidence = CurvatureConfidence_unavailable;
    // bvc.curvatureCalculationMode = CurvatureCalculationMode_yawRateUsed;

    // bvc.yawRate.yawRateValue = YawRateValue_unavailable;
    //-------------------------CAM-------------------------//

    //-------------------------DENM-------------------------//
    DecentralizedEnvironmentalNotificationMessage_t& denm = message->denm;
    ManagementContainer_t& management = denm.management;
    management.actionID.originatingStationID = 4;
    management.actionID.sequenceNumber = 1000;

    asn_uint642INTEGER(&management.detectionTime, TimestampIts_oneMillisecAfterUTCStartOf2004);
    asn_uint642INTEGER(&management.referenceTime, (long)time_now.count());
    management.eventPosition.longitude = round(position.longitude, microdegree) * Longitude_oneMicrodegreeEast;
    management.eventPosition.latitude = round(position.latitude, microdegree) * Latitude_oneMicrodegreeNorth;
    management.eventPosition.positionConfidenceEllipse.semiMajorOrientation = HeadingValue_unavailable;
    management.eventPosition.positionConfidenceEllipse.semiMajorConfidence = SemiAxisLength_unavailable;
    management.eventPosition.positionConfidenceEllipse.semiMinorConfidence = SemiAxisLength_unavailable;
    if (position.altitude) {
        management.eventPosition.altitude.altitudeValue = to_altitude_value(position.altitude->value());
        management.eventPosition.altitude.altitudeConfidence = to_altitude_confidence(position.altitude->confidence());
    } else {
        management.eventPosition.altitude.altitudeValue = AltitudeValue_unavailable;
        management.eventPosition.altitude.altitudeConfidence = AltitudeConfidence_unavailable;
    }
    management.stationType = StationType_pedestrian;

    denm.situation = vanetza::asn1::allocate<SituationContainer>();
    denm.situation->informationQuality = InformationQuality_highest;
    denm.situation->eventType.causeCode = CauseCodeType_hazardousLocation_ObstacleOnTheRoad;
    denm.situation->eventType.subCauseCode = CollisionRiskSubCauseCode::CollisionRiskSubCauseCode_unavailable;;

    //-------------------------DENM-------------------------//

    std::string error;
    if (!message.validate(error)) {
        // throw std::runtime_error("Invalid high frequency CAM: %s" + error);
        throw std::runtime_error("Invalid high frequency DENM: %s" + error);
    }

    DownPacketPtr packet { new DownPacket() };
    packet->layer(OsiLayer::Application) = std::move(message);

    DataRequest request;
    request.its_aid = aid::CA;
    request.transport_type = geonet::TransportType::SHB;
    request.communication_profile = geonet::CommunicationProfile::ITS_G5;

    auto confirm = Application::request(request, std::move(packet));
    if (!confirm.accepted()) {
        // throw std::runtime_error("CAM application data request failed");
        throw std::runtime_error("DENM application data request failed");
    }

    schedule_timer();
}
