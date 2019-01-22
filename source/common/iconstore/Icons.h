#pragma once

#include <QString>
#include <QVector>

#include "IconFontStore.h"

namespace Quartz {

enum class IconFontFamily {
    Any,
    Material,
    FontAwesome,
    FontAwesomeBrands,
    Custom,
};

struct IconInfo {
    int m_code;
    QString m_strCode;
    IconFontFamily m_font;
    QString m_fontName;
    QString m_id;
    QString m_name;
};

const QVector<IconInfo> ICON_INFO = {
    {
        0xE84D,
        "0xE84D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Rotation_3d",
        "Rotation 3D"
    },
    {
        0xEB3B,
        "0xEB3B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AcUnit",
        "Ac Unit"
    },
    {
        0xE190,
        "0xE190",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AccessAlarm",
        "Access Alarm"
    },
    {
        0xE191,
        "0xE191",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AccessAlarms",
        "Access Alarms"
    },
    {
        0xE192,
        "0xE192",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AccessTime",
        "Access Time"
    },
    {
        0xE84E,
        "0xE84E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Accessibility",
        "Accessibility"
    },
    {
        0xE914,
        "0xE914",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Accessible",
        "Accessible"
    },
    {
        0xE84F,
        "0xE84F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AccountBalance",
        "Account Balance"
    },
    {
        0xE850,
        "0xE850",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AccountBalanceWallet",
        "Account Balance Wallet"
    },
    {
        0xE851,
        "0xE851",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AccountBox",
        "Account Box"
    },
    {
        0xE853,
        "0xE853",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AccountCircle",
        "Account Circle"
    },
    {
        0xE60E,
        "0xE60E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Adb",
        "Adb"
    },
    {
        0xE145,
        "0xE145",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Add",
        "Add"
    },
    {
        0xE439,
        "0xE439",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AddAPhoto",
        "Add A Photo"
    },
    {
        0xE193,
        "0xE193",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AddAlarm",
        "Add Alarm"
    },
    {
        0xE003,
        "0xE003",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AddAlert",
        "Add Alert"
    },
    {
        0xE146,
        "0xE146",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AddBox",
        "Add Box"
    },
    {
        0xE147,
        "0xE147",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AddCircle",
        "Add Circle"
    },
    {
        0xE148,
        "0xE148",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AddCircleOutline",
        "Add Circle Outline"
    },
    {
        0xE567,
        "0xE567",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AddLocation",
        "Add Location"
    },
    {
        0xE854,
        "0xE854",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AddShoppingCart",
        "Add Shopping Cart"
    },
    {
        0xE39D,
        "0xE39D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AddToPhotos",
        "Add To Photos"
    },
    {
        0xE05C,
        "0xE05C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AddToQueue",
        "Add To Queue"
    },
    {
        0xE39E,
        "0xE39E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Adjust",
        "Adjust"
    },
    {
        0xE630,
        "0xE630",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AirlineSeatFlat",
        "Airline Seat Flat"
    },
    {
        0xE631,
        "0xE631",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AirlineSeatFlatAngled",
        "Airline Seat Flat Angled"
    },
    {
        0xE632,
        "0xE632",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AirlineSeatIndividualSuite",
        "Airline Seat Individual Suite"
    },
    {
        0xE633,
        "0xE633",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AirlineSeatLegroomExtra",
        "Airline Seat Legroom Extra"
    },
    {
        0xE634,
        "0xE634",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AirlineSeatLegroomNormal",
        "Airline Seat Legroom Normal"
    },
    {
        0xE635,
        "0xE635",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AirlineSeatLegroomReduced",
        "Airline Seat Legroom Reduced"
    },
    {
        0xE636,
        "0xE636",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AirlineSeatReclineExtra",
        "Airline Seat Recline Extra"
    },
    {
        0xE637,
        "0xE637",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AirlineSeatReclineNormal",
        "Airline Seat Recline Normal"
    },
    {
        0xE195,
        "0xE195",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AirplanemodeActive",
        "Airplanemode Active"
    },
    {
        0xE194,
        "0xE194",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AirplanemodeInactive",
        "Airplanemode Inactive"
    },
    {
        0xE055,
        "0xE055",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Airplay",
        "Airplay"
    },
    {
        0xEB3C,
        "0xEB3C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AirportShuttle",
        "Airport Shuttle"
    },
    {
        0xE855,
        "0xE855",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Alarm",
        "Alarm"
    },
    {
        0xE856,
        "0xE856",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AlarmAdd",
        "Alarm Add"
    },
    {
        0xE857,
        "0xE857",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AlarmOff",
        "Alarm Off"
    },
    {
        0xE858,
        "0xE858",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AlarmOn",
        "Alarm On"
    },
    {
        0xE019,
        "0xE019",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Album",
        "Album"
    },
    {
        0xEB3D,
        "0xEB3D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AllInclusive",
        "All Inclusive"
    },
    {
        0xE90B,
        "0xE90B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AllOut",
        "All Out"
    },
    {
        0xE859,
        "0xE859",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Android",
        "Android"
    },
    {
        0xE85A,
        "0xE85A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Announcement",
        "Announcement"
    },
    {
        0xE5C3,
        "0xE5C3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Apps",
        "Apps"
    },
    {
        0xE149,
        "0xE149",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Archive",
        "Archive"
    },
    {
        0xE5C4,
        "0xE5C4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ArrowBack",
        "Arrow Back"
    },
    {
        0xE5DB,
        "0xE5DB",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ArrowDownward",
        "Arrow Downward"
    },
    {
        0xE5C5,
        "0xE5C5",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ArrowDropDown",
        "Arrow Drop Down"
    },
    {
        0xE5C6,
        "0xE5C6",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ArrowDropDownCircle",
        "Arrow Drop Down Circle"
    },
    {
        0xE5C7,
        "0xE5C7",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ArrowDropUp",
        "Arrow Drop Up"
    },
    {
        0xE5C8,
        "0xE5C8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ArrowForward",
        "Arrow Forward"
    },
    {
        0xE5D8,
        "0xE5D8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ArrowUpward",
        "Arrow Upward"
    },
    {
        0xE060,
        "0xE060",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ArtTrack",
        "Art Track"
    },
    {
        0xE85B,
        "0xE85B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AspectRatio",
        "Aspect Ratio"
    },
    {
        0xE85C,
        "0xE85C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Assessment",
        "Assessment"
    },
    {
        0xE85D,
        "0xE85D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Assignment",
        "Assignment"
    },
    {
        0xE85E,
        "0xE85E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AssignmentInd",
        "Assignment Ind"
    },
    {
        0xE85F,
        "0xE85F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AssignmentLate",
        "Assignment Late"
    },
    {
        0xE860,
        "0xE860",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AssignmentReturn",
        "Assignment Return"
    },
    {
        0xE861,
        "0xE861",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AssignmentReturned",
        "Assignment Returned"
    },
    {
        0xE862,
        "0xE862",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AssignmentTurnedIn",
        "Assignment Turned In"
    },
    {
        0xE39F,
        "0xE39F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Assistant",
        "Assistant"
    },
    {
        0xE3A0,
        "0xE3A0",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AssistantPhoto",
        "Assistant Photo"
    },
    {
        0xE226,
        "0xE226",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AttachFile",
        "Attach File"
    },
    {
        0xE227,
        "0xE227",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AttachMoney",
        "Attach Money"
    },
    {
        0xE2BC,
        "0xE2BC",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Attachment",
        "Attachment"
    },
    {
        0xE3A1,
        "0xE3A1",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Audiotrack",
        "Audiotrack"
    },
    {
        0xE863,
        "0xE863",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Autorenew",
        "Autorenew"
    },
    {
        0xE01B,
        "0xE01B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::AvTimer",
        "Av Timer"
    },
    {
        0xE14A,
        "0xE14A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Backspace",
        "Backspace"
    },
    {
        0xE864,
        "0xE864",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Backup",
        "Backup"
    },
    {
        0xE19C,
        "0xE19C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BatteryAlert",
        "Battery Alert"
    },
    {
        0xE1A3,
        "0xE1A3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BatteryChargingFull",
        "Battery Charging Full"
    },
    {
        0xE1A4,
        "0xE1A4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BatteryFull",
        "Battery Full"
    },
    {
        0xE1A5,
        "0xE1A5",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BatteryStd",
        "Battery Std"
    },
    {
        0xE1A6,
        "0xE1A6",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BatteryUnknown",
        "Battery Unknown"
    },
    {
        0xEB3E,
        "0xEB3E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BeachAccess",
        "Beach Access"
    },
    {
        0xE52D,
        "0xE52D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Beenhere",
        "Beenhere"
    },
    {
        0xE14B,
        "0xE14B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Block",
        "Block"
    },
    {
        0xE1A7,
        "0xE1A7",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Bluetooth",
        "Bluetooth"
    },
    {
        0xE60F,
        "0xE60F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BluetoothAudio",
        "Bluetooth Audio"
    },
    {
        0xE1A8,
        "0xE1A8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BluetoothConnected",
        "Bluetooth Connected"
    },
    {
        0xE1A9,
        "0xE1A9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BluetoothDisabled",
        "Bluetooth Disabled"
    },
    {
        0xE1AA,
        "0xE1AA",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BluetoothSearching",
        "Bluetooth Searching"
    },
    {
        0xE3A2,
        "0xE3A2",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BlurCircular",
        "Blur Circular"
    },
    {
        0xE3A3,
        "0xE3A3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BlurLinear",
        "Blur Linear"
    },
    {
        0xE3A4,
        "0xE3A4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BlurOff",
        "Blur Off"
    },
    {
        0xE3A5,
        "0xE3A5",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BlurOn",
        "Blur On"
    },
    {
        0xE865,
        "0xE865",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Book",
        "Book"
    },
    {
        0xE866,
        "0xE866",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Bookmark",
        "Bookmark"
    },
    {
        0xE867,
        "0xE867",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BookmarkBorder",
        "Bookmark Border"
    },
    {
        0xE228,
        "0xE228",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BorderAll",
        "Border All"
    },
    {
        0xE229,
        "0xE229",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BorderBottom",
        "Border Bottom"
    },
    {
        0xE22A,
        "0xE22A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BorderClear",
        "Border Clear"
    },
    {
        0xE22B,
        "0xE22B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BorderColor",
        "Border Color"
    },
    {
        0xE22C,
        "0xE22C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BorderHorizontal",
        "Border Horizontal"
    },
    {
        0xE22D,
        "0xE22D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BorderInner",
        "Border Inner"
    },
    {
        0xE22E,
        "0xE22E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BorderLeft",
        "Border Left"
    },
    {
        0xE22F,
        "0xE22F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BorderOuter",
        "Border Outer"
    },
    {
        0xE230,
        "0xE230",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BorderRight",
        "Border Right"
    },
    {
        0xE231,
        "0xE231",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BorderStyle",
        "Border Style"
    },
    {
        0xE232,
        "0xE232",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BorderTop",
        "Border Top"
    },
    {
        0xE233,
        "0xE233",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BorderVertical",
        "Border Vertical"
    },
    {
        0xE06B,
        "0xE06B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BrandingWatermark",
        "Branding Watermark"
    },
    {
        0xE3A6,
        "0xE3A6",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Brightness_1",
        "Brightness _ 1"
    },
    {
        0xE3A7,
        "0xE3A7",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Brightness_2",
        "Brightness _ 2"
    },
    {
        0xE3A8,
        "0xE3A8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Brightness_3",
        "Brightness _ 3"
    },
    {
        0xE3A9,
        "0xE3A9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Brightness_4",
        "Brightness _ 4"
    },
    {
        0xE3AA,
        "0xE3AA",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Brightness_5",
        "Brightness _ 5"
    },
    {
        0xE3AB,
        "0xE3AB",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Brightness_6",
        "Brightness _ 6"
    },
    {
        0xE3AC,
        "0xE3AC",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Brightness_7",
        "Brightness _ 7"
    },
    {
        0xE1AB,
        "0xE1AB",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BrightnessAuto",
        "Brightness Auto"
    },
    {
        0xE1AC,
        "0xE1AC",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BrightnessHigh",
        "Brightness High"
    },
    {
        0xE1AD,
        "0xE1AD",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BrightnessLow",
        "Brightness Low"
    },
    {
        0xE1AE,
        "0xE1AE",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BrightnessMedium",
        "Brightness Medium"
    },
    {
        0xE3AD,
        "0xE3AD",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BrokenImage",
        "Broken Image"
    },
    {
        0xE3AE,
        "0xE3AE",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Brush",
        "Brush"
    },
    {
        0xE6DD,
        "0xE6DD",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BubbleChart",
        "Bubble Chart"
    },
    {
        0xE868,
        "0xE868",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BugReport",
        "Bug Report"
    },
    {
        0xE869,
        "0xE869",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Build",
        "Build"
    },
    {
        0xE43C,
        "0xE43C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BurstMode",
        "Burst Mode"
    },
    {
        0xE0AF,
        "0xE0AF",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Business",
        "Business"
    },
    {
        0xEB3F,
        "0xEB3F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::BusinessCenter",
        "Business Center"
    },
    {
        0xE86A,
        "0xE86A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Cached",
        "Cached"
    },
    {
        0xE7E9,
        "0xE7E9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Cake",
        "Cake"
    },
    {
        0xE0B0,
        "0xE0B0",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Call",
        "Call"
    },
    {
        0xE0B1,
        "0xE0B1",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CallEnd",
        "Call End"
    },
    {
        0xE0B2,
        "0xE0B2",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CallMade",
        "Call Made"
    },
    {
        0xE0B3,
        "0xE0B3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CallMerge",
        "Call Merge"
    },
    {
        0xE0B4,
        "0xE0B4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CallMissed",
        "Call Missed"
    },
    {
        0xE0E4,
        "0xE0E4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CallMissedOutgoing",
        "Call Missed Outgoing"
    },
    {
        0xE0B5,
        "0xE0B5",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CallReceived",
        "Call Received"
    },
    {
        0xE0B6,
        "0xE0B6",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CallSplit",
        "Call Split"
    },
    {
        0xE06C,
        "0xE06C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CallToAction",
        "Call To Action"
    },
    {
        0xE3AF,
        "0xE3AF",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Camera",
        "Camera"
    },
    {
        0xE3B0,
        "0xE3B0",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CameraAlt",
        "Camera Alt"
    },
    {
        0xE8FC,
        "0xE8FC",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CameraEnhance",
        "Camera Enhance"
    },
    {
        0xE3B1,
        "0xE3B1",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CameraFront",
        "Camera Front"
    },
    {
        0xE3B2,
        "0xE3B2",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CameraRear",
        "Camera Rear"
    },
    {
        0xE3B3,
        "0xE3B3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CameraRoll",
        "Camera Roll"
    },
    {
        0xE5C9,
        "0xE5C9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Cancel",
        "Cancel"
    },
    {
        0xE8F6,
        "0xE8F6",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CardGiftcard",
        "Card Giftcard"
    },
    {
        0xE8F7,
        "0xE8F7",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CardMembership",
        "Card Membership"
    },
    {
        0xE8F8,
        "0xE8F8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CardTravel",
        "Card Travel"
    },
    {
        0xEB40,
        "0xEB40",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Casino",
        "Casino"
    },
    {
        0xE307,
        "0xE307",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Cast",
        "Cast"
    },
    {
        0xE308,
        "0xE308",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CastConnected",
        "Cast Connected"
    },
    {
        0xE3B4,
        "0xE3B4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CenterFocusStrong",
        "Center Focus Strong"
    },
    {
        0xE3B5,
        "0xE3B5",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CenterFocusWeak",
        "Center Focus Weak"
    },
    {
        0xE86B,
        "0xE86B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ChangeHistory",
        "Change History"
    },
    {
        0xE0B7,
        "0xE0B7",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Chat",
        "Chat"
    },
    {
        0xE0CA,
        "0xE0CA",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ChatBubble",
        "Chat Bubble"
    },
    {
        0xE0CB,
        "0xE0CB",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ChatBubbleOutline",
        "Chat Bubble Outline"
    },
    {
        0xE5CA,
        "0xE5CA",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Check",
        "Check"
    },
    {
        0xE834,
        "0xE834",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CheckBox",
        "Check Box"
    },
    {
        0xE835,
        "0xE835",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CheckBoxOutlineBlank",
        "Check Box Outline Blank"
    },
    {
        0xE86C,
        "0xE86C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CheckCircle",
        "Check Circle"
    },
    {
        0xE5CB,
        "0xE5CB",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ChevronLeft",
        "Chevron Left"
    },
    {
        0xE5CC,
        "0xE5CC",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ChevronRight",
        "Chevron Right"
    },
    {
        0xEB41,
        "0xEB41",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ChildCare",
        "Child Care"
    },
    {
        0xEB42,
        "0xEB42",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ChildFriendly",
        "Child Friendly"
    },
    {
        0xE86D,
        "0xE86D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ChromeReaderMode",
        "Chrome Reader Mode"
    },
    {
        0xE86E,
        "0xE86E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Class",
        "Class"
    },
    {
        0xE14C,
        "0xE14C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Clear",
        "Clear"
    },
    {
        0xE0B8,
        "0xE0B8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ClearAll",
        "Clear All"
    },
    {
        0xE5CD,
        "0xE5CD",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Close",
        "Close"
    },
    {
        0xE01C,
        "0xE01C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ClosedCaption",
        "Closed Caption"
    },
    {
        0xE2BD,
        "0xE2BD",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Cloud",
        "Cloud"
    },
    {
        0xE2BE,
        "0xE2BE",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CloudCircle",
        "Cloud Circle"
    },
    {
        0xE2BF,
        "0xE2BF",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CloudDone",
        "Cloud Done"
    },
    {
        0xE2C0,
        "0xE2C0",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CloudDownload",
        "Cloud Download"
    },
    {
        0xE2C1,
        "0xE2C1",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CloudOff",
        "Cloud Off"
    },
    {
        0xE2C2,
        "0xE2C2",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CloudQueue",
        "Cloud Queue"
    },
    {
        0xE2C3,
        "0xE2C3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CloudUpload",
        "Cloud Upload"
    },
    {
        0xE86F,
        "0xE86F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Code",
        "Code"
    },
    {
        0xE3B6,
        "0xE3B6",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Collections",
        "Collections"
    },
    {
        0xE431,
        "0xE431",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CollectionsBookmark",
        "Collections Bookmark"
    },
    {
        0xE3B7,
        "0xE3B7",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ColorLens",
        "Color Lens"
    },
    {
        0xE3B8,
        "0xE3B8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Colorize",
        "Colorize"
    },
    {
        0xE0B9,
        "0xE0B9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Comment",
        "Comment"
    },
    {
        0xE3B9,
        "0xE3B9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Compare",
        "Compare"
    },
    {
        0xE915,
        "0xE915",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CompareArrows",
        "Compare Arrows"
    },
    {
        0xE30A,
        "0xE30A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Computer",
        "Computer"
    },
    {
        0xE638,
        "0xE638",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ConfirmationNumber",
        "Confirmation Number"
    },
    {
        0xE0D0,
        "0xE0D0",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ContactMail",
        "Contact Mail"
    },
    {
        0xE0CF,
        "0xE0CF",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ContactPhone",
        "Contact Phone"
    },
    {
        0xE0BA,
        "0xE0BA",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Contacts",
        "Contacts"
    },
    {
        0xE14D,
        "0xE14D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ContentCopy",
        "Content Copy"
    },
    {
        0xE14E,
        "0xE14E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ContentCut",
        "Content Cut"
    },
    {
        0xE14F,
        "0xE14F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ContentPaste",
        "Content Paste"
    },
    {
        0xE3BA,
        "0xE3BA",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ControlPoint",
        "Control Point"
    },
    {
        0xE3BB,
        "0xE3BB",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ControlPointDuplicate",
        "Control Point Duplicate"
    },
    {
        0xE90C,
        "0xE90C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Copyright",
        "Copyright"
    },
    {
        0xE150,
        "0xE150",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Create",
        "Create"
    },
    {
        0xE2CC,
        "0xE2CC",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CreateNewFolder",
        "Create New Folder"
    },
    {
        0xE870,
        "0xE870",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CreditCard",
        "Credit Card"
    },
    {
        0xE3BE,
        "0xE3BE",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Crop",
        "Crop"
    },
    {
        0xE3BC,
        "0xE3BC",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Crop_16_9",
        "Crop 16x9"
    },
    {
        0xE3BD,
        "0xE3BD",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Crop_3_2",
        "Crop 3x2"
    },
    {
        0xE3BF,
        "0xE3BF",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Crop_5_4",
        "Crop 5x4"
    },
    {
        0xE3C0,
        "0xE3C0",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Crop_7_5",
        "Crop 7x5"
    },
    {
        0xE3C1,
        "0xE3C1",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CropDin",
        "Crop Din"
    },
    {
        0xE3C2,
        "0xE3C2",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CropFree",
        "Crop Free"
    },
    {
        0xE3C3,
        "0xE3C3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CropLandscape",
        "Crop Landscape"
    },
    {
        0xE3C4,
        "0xE3C4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CropOriginal",
        "Crop Original"
    },
    {
        0xE3C5,
        "0xE3C5",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CropPortrait",
        "Crop Portrait"
    },
    {
        0xE437,
        "0xE437",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CropRotate",
        "Crop Rotate"
    },
    {
        0xE3C6,
        "0xE3C6",
        IconFontFamily::Material,
        "Material",
        "MatIcon::CropSquare",
        "Crop Square"
    },
    {
        0xE871,
        "0xE871",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Dashboard",
        "Dashboard"
    },
    {
        0xE1AF,
        "0xE1AF",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DataUsage",
        "Data Usage"
    },
    {
        0xE916,
        "0xE916",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DateRange",
        "Date Range"
    },
    {
        0xE3C7,
        "0xE3C7",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Dehaze",
        "Dehaze"
    },
    {
        0xE872,
        "0xE872",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Delete",
        "Delete"
    },
    {
        0xE92B,
        "0xE92B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DeleteForever",
        "Delete Forever"
    },
    {
        0xE16C,
        "0xE16C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DeleteSweep",
        "Delete Sweep"
    },
    {
        0xE873,
        "0xE873",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Description",
        "Description"
    },
    {
        0xE30B,
        "0xE30B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DesktopMac",
        "Desktop Mac"
    },
    {
        0xE30C,
        "0xE30C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DesktopWindows",
        "Desktop Windows"
    },
    {
        0xE3C8,
        "0xE3C8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Details",
        "Details"
    },
    {
        0xE30D,
        "0xE30D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DeveloperBoard",
        "Developer Board"
    },
    {
        0xE1B0,
        "0xE1B0",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DeveloperMode",
        "Developer Mode"
    },
    {
        0xE335,
        "0xE335",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DeviceHub",
        "Device Hub"
    },
    {
        0xE1B1,
        "0xE1B1",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Devices",
        "Devices"
    },
    {
        0xE337,
        "0xE337",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DevicesOther",
        "Devices Other"
    },
    {
        0xE0BB,
        "0xE0BB",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DialerSip",
        "Dialer Sip"
    },
    {
        0xE0BC,
        "0xE0BC",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Dialpad",
        "Dialpad"
    },
    {
        0xE52E,
        "0xE52E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Directions",
        "Directions"
    },
    {
        0xE52F,
        "0xE52F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DirectionsBike",
        "Directions Bike"
    },
    {
        0xE532,
        "0xE532",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DirectionsBoat",
        "Directions Boat"
    },
    {
        0xE530,
        "0xE530",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DirectionsBus",
        "Directions Bus"
    },
    {
        0xE531,
        "0xE531",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DirectionsCar",
        "Directions Car"
    },
    {
        0xE534,
        "0xE534",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DirectionsRailway",
        "Directions Railway"
    },
    {
        0xE566,
        "0xE566",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DirectionsRun",
        "Directions Run"
    },
    {
        0xE533,
        "0xE533",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DirectionsSubway",
        "Directions Subway"
    },
    {
        0xE535,
        "0xE535",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DirectionsTransit",
        "Directions Transit"
    },
    {
        0xE536,
        "0xE536",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DirectionsWalk",
        "Directions Walk"
    },
    {
        0xE610,
        "0xE610",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DiscFull",
        "Disc Full"
    },
    {
        0xE875,
        "0xE875",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Dns",
        "Dns"
    },
    {
        0xE612,
        "0xE612",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DoNotDisturb",
        "Do Not Disturb"
    },
    {
        0xE611,
        "0xE611",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DoNotDisturbAlt",
        "Do Not Disturb Alt"
    },
    {
        0xE643,
        "0xE643",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DoNotDisturbOff",
        "Do Not Disturb Off"
    },
    {
        0xE644,
        "0xE644",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DoNotDisturbOn",
        "Do Not Disturb On"
    },
    {
        0xE30E,
        "0xE30E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Dock",
        "Dock"
    },
    {
        0xE7EE,
        "0xE7EE",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Domain",
        "Domain"
    },
    {
        0xE876,
        "0xE876",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Done",
        "Done"
    },
    {
        0xE877,
        "0xE877",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DoneAll",
        "Done All"
    },
    {
        0xE917,
        "0xE917",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DonutLarge",
        "Donut Large"
    },
    {
        0xE918,
        "0xE918",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DonutSmall",
        "Donut Small"
    },
    {
        0xE151,
        "0xE151",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Drafts",
        "Drafts"
    },
    {
        0xE25D,
        "0xE25D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DragHandle",
        "Drag Handle"
    },
    {
        0xE613,
        "0xE613",
        IconFontFamily::Material,
        "Material",
        "MatIcon::DriveEta",
        "Drive Eta"
    },
    {
        0xE1B2,
        "0xE1B2",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Dvr",
        "Dvr"
    },
    {
        0xE3C9,
        "0xE3C9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Edit",
        "Edit"
    },
    {
        0xE568,
        "0xE568",
        IconFontFamily::Material,
        "Material",
        "MatIcon::EditLocation",
        "Edit Location"
    },
    {
        0xE8FB,
        "0xE8FB",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Eject",
        "Eject"
    },
    {
        0xE0BE,
        "0xE0BE",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Email",
        "Email"
    },
    {
        0xE63F,
        "0xE63F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::EnhancedEncryption",
        "Enhanced Encryption"
    },
    {
        0xE01D,
        "0xE01D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Equalizer",
        "Equalizer"
    },
    {
        0xE000,
        "0xE000",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Error",
        "Error"
    },
    {
        0xE001,
        "0xE001",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ErrorOutline",
        "Error Outline"
    },
    {
        0xE926,
        "0xE926",
        IconFontFamily::Material,
        "Material",
        "MatIcon::EuroSymbol",
        "Euro Symbol"
    },
    {
        0xE56D,
        "0xE56D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::EvStation",
        "Ev Station"
    },
    {
        0xE878,
        "0xE878",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Event",
        "Event"
    },
    {
        0xE614,
        "0xE614",
        IconFontFamily::Material,
        "Material",
        "MatIcon::EventAvailable",
        "Event Available"
    },
    {
        0xE615,
        "0xE615",
        IconFontFamily::Material,
        "Material",
        "MatIcon::EventBusy",
        "Event Busy"
    },
    {
        0xE616,
        "0xE616",
        IconFontFamily::Material,
        "Material",
        "MatIcon::EventNote",
        "Event Note"
    },
    {
        0xE903,
        "0xE903",
        IconFontFamily::Material,
        "Material",
        "MatIcon::EventSeat",
        "Event Seat"
    },
    {
        0xE879,
        "0xE879",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ExitToApp",
        "Exit To App"
    },
    {
        0xE5CE,
        "0xE5CE",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ExpandLess",
        "Expand Less"
    },
    {
        0xE5CF,
        "0xE5CF",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ExpandMore",
        "Expand More"
    },
    {
        0xE01E,
        "0xE01E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Explicit",
        "Explicit"
    },
    {
        0xE87A,
        "0xE87A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Explore",
        "Explore"
    },
    {
        0xE3CA,
        "0xE3CA",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Exposure",
        "Exposure"
    },
    {
        0xE3CB,
        "0xE3CB",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ExposureNeg_1",
        "Exposure Neg 1"
    },
    {
        0xE3CC,
        "0xE3CC",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ExposureNeg_2",
        "Exposure Neg 2"
    },
    {
        0xE3CD,
        "0xE3CD",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ExposurePlus_1",
        "Exposure Plus 1"
    },
    {
        0xE3CE,
        "0xE3CE",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ExposurePlus_2",
        "Exposure Plus 2"
    },
    {
        0xE3CF,
        "0xE3CF",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ExposureZero",
        "Exposure Zero"
    },
    {
        0xE87B,
        "0xE87B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Extension",
        "Extension"
    },
    {
        0xE87C,
        "0xE87C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Face",
        "Face"
    },
    {
        0xE01F,
        "0xE01F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FastForward",
        "Fast Forward"
    },
    {
        0xE020,
        "0xE020",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FastRewind",
        "Fast Rewind"
    },
    {
        0xE87D,
        "0xE87D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Favorite",
        "Favorite"
    },
    {
        0xE87E,
        "0xE87E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FavoriteBorder",
        "Favorite Border"
    },
    {
        0xE06D,
        "0xE06D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FeaturedPlayList",
        "Featured Play List"
    },
    {
        0xE06E,
        "0xE06E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FeaturedVideo",
        "Featured Video"
    },
    {
        0xE87F,
        "0xE87F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Feedback",
        "Feedback"
    },
    {
        0xE05D,
        "0xE05D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FiberDvr",
        "Fiber Dvr"
    },
    {
        0xE061,
        "0xE061",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FiberManualRecord",
        "Fiber Manual Record"
    },
    {
        0xE05E,
        "0xE05E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FiberNew",
        "Fiber New"
    },
    {
        0xE06A,
        "0xE06A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FiberPin",
        "Fiber Pin"
    },
    {
        0xE062,
        "0xE062",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FiberSmartRecord",
        "Fiber Smart Record"
    },
    {
        0xE2C4,
        "0xE2C4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FileDownload",
        "File Download"
    },
    {
        0xE2C6,
        "0xE2C6",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FileUpload",
        "File Upload"
    },
    {
        0xE3D3,
        "0xE3D3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Filter",
        "Filter"
    },
    {
        0xE3D0,
        "0xE3D0",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Filter_1",
        "Filter 1"
    },
    {
        0xE3D1,
        "0xE3D1",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Filter_2",
        "Filter 2"
    },
    {
        0xE3D2,
        "0xE3D2",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Filter_3",
        "Filter 3"
    },
    {
        0xE3D4,
        "0xE3D4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Filter_4",
        "Filter 4"
    },
    {
        0xE3D5,
        "0xE3D5",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Filter_5",
        "Filter 5"
    },
    {
        0xE3D6,
        "0xE3D6",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Filter_6",
        "Filter 6"
    },
    {
        0xE3D7,
        "0xE3D7",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Filter_7",
        "Filter 7"
    },
    {
        0xE3D8,
        "0xE3D8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Filter_8",
        "Filter 8"
    },
    {
        0xE3D9,
        "0xE3D9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Filter_9",
        "Filter 9"
    },
    {
        0xE3DA,
        "0xE3DA",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Filter_9Plus",
        "Filter 9 Plus"
    },
    {
        0xE3DB,
        "0xE3DB",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FilterBAndW",
        "Filter B And W"
    },
    {
        0xE3DC,
        "0xE3DC",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FilterCenterFocus",
        "Filter Center Focus"
    },
    {
        0xE3DD,
        "0xE3DD",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FilterDrama",
        "Filter Drama"
    },
    {
        0xE3DE,
        "0xE3DE",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FilterFrames",
        "Filter Frames"
    },
    {
        0xE3DF,
        "0xE3DF",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FilterHdr",
        "Filter Hdr"
    },
    {
        0xE152,
        "0xE152",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FilterList",
        "Filter List"
    },
    {
        0xE3E0,
        "0xE3E0",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FilterNone",
        "Filter None"
    },
    {
        0xE3E2,
        "0xE3E2",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FilterTiltShift",
        "Filter Tilt Shift"
    },
    {
        0xE3E3,
        "0xE3E3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FilterVintage",
        "Filter Vintage"
    },
    {
        0xE880,
        "0xE880",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FindInPage",
        "Find In Page"
    },
    {
        0xE881,
        "0xE881",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FindReplace",
        "Find Replace"
    },
    {
        0xE90D,
        "0xE90D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Fingerprint",
        "Fingerprint"
    },
    {
        0xE5DC,
        "0xE5DC",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FirstPage",
        "First Page"
    },
    {
        0xEB43,
        "0xEB43",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FitnessCenter",
        "Fitness Center"
    },
    {
        0xE153,
        "0xE153",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Flag",
        "Flag"
    },
    {
        0xE3E4,
        "0xE3E4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Flare",
        "Flare"
    },
    {
        0xE3E5,
        "0xE3E5",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FlashAuto",
        "Flash Auto"
    },
    {
        0xE3E6,
        "0xE3E6",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FlashOff",
        "Flash Off"
    },
    {
        0xE3E7,
        "0xE3E7",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FlashOn",
        "Flash On"
    },
    {
        0xE539,
        "0xE539",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Flight",
        "Flight"
    },
    {
        0xE904,
        "0xE904",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FlightLand",
        "Flight Land"
    },
    {
        0xE905,
        "0xE905",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FlightTakeoff",
        "Flight Takeoff"
    },
    {
        0xE3E8,
        "0xE3E8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Flip",
        "Flip"
    },
    {
        0xE882,
        "0xE882",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FlipToBack",
        "Flip To Back"
    },
    {
        0xE883,
        "0xE883",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FlipToFront",
        "Flip To Front"
    },
    {
        0xE2C7,
        "0xE2C7",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Folder",
        "Folder"
    },
    {
        0xE2C8,
        "0xE2C8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FolderOpen",
        "Folder Open"
    },
    {
        0xE2C9,
        "0xE2C9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FolderShared",
        "Folder Shared"
    },
    {
        0xE617,
        "0xE617",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FolderSpecial",
        "Folder Special"
    },
    {
        0xE167,
        "0xE167",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FontDownload",
        "Font Download"
    },
    {
        0xE234,
        "0xE234",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatAlignCenter",
        "Format Align Center"
    },
    {
        0xE235,
        "0xE235",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatAlignJustify",
        "Format Align Justify"
    },
    {
        0xE236,
        "0xE236",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatAlignLeft",
        "Format Align Left"
    },
    {
        0xE237,
        "0xE237",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatAlignRight",
        "Format Align Right"
    },
    {
        0xE238,
        "0xE238",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatBold",
        "Format Bold"
    },
    {
        0xE239,
        "0xE239",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatClear",
        "Format Clear"
    },
    {
        0xE23A,
        "0xE23A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatColorFill",
        "Format Color Fill"
    },
    {
        0xE23B,
        "0xE23B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatColorReset",
        "Format Color Reset"
    },
    {
        0xE23C,
        "0xE23C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatColorText",
        "Format Color Text"
    },
    {
        0xE23D,
        "0xE23D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatIndentDecrease",
        "Format Indent Decrease"
    },
    {
        0xE23E,
        "0xE23E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatIndentIncrease",
        "Format Indent Increase"
    },
    {
        0xE23F,
        "0xE23F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatItalic",
        "Format Italic"
    },
    {
        0xE240,
        "0xE240",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatLineSpacing",
        "Format Line Spacing"
    },
    {
        0xE241,
        "0xE241",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatListBulleted",
        "Format List Bulleted"
    },
    {
        0xE242,
        "0xE242",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatListNumbered",
        "Format List Numbered"
    },
    {
        0xE243,
        "0xE243",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatPaint",
        "Format Paint"
    },
    {
        0xE244,
        "0xE244",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatQuote",
        "Format Quote"
    },
    {
        0xE25E,
        "0xE25E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatShapes",
        "Format Shapes"
    },
    {
        0xE245,
        "0xE245",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatSize",
        "Format Size"
    },
    {
        0xE246,
        "0xE246",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatStrikethrough",
        "Format Strikethrough"
    },
    {
        0xe247,
        "0xe247",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatTextdirectionLToR",
        "Format Textdirection L To R"
    },
    {
        0xe248,
        "0xe248",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatTextdirectionRToL",
        "Format Textdirection R To L"
    },
    {
        0xE249,
        "0xE249",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FormatUnderlined",
        "Format Underlined"
    },
    {
        0xE0BF,
        "0xE0BF",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Forum",
        "Forum"
    },
    {
        0xE154,
        "0xE154",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Forward",
        "Forward"
    },
    {
        0xE056,
        "0xE056",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Forward_10",
        "Forward 10"
    },
    {
        0xE057,
        "0xE057",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Forward_30",
        "Forward 30"
    },
    {
        0xE058,
        "0xE058",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Forward_5",
        "Forward 5"
    },
    {
        0xEB44,
        "0xEB44",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FreeBreakfast",
        "Free Breakfast"
    },
    {
        0xE5D0,
        "0xE5D0",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Fullscreen",
        "Fullscreen"
    },
    {
        0xE5D1,
        "0xE5D1",
        IconFontFamily::Material,
        "Material",
        "MatIcon::FullscreenExit",
        "Fullscreen Exit"
    },
    {
        0xE24A,
        "0xE24A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Functions",
        "Functions"
    },
    {
        0xE927,
        "0xE927",
        IconFontFamily::Material,
        "Material",
        "MatIcon::GTranslate",
        "G Translate"
    },
    {
        0xE30F,
        "0xE30F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Gamepad",
        "Gamepad"
    },
    {
        0xE021,
        "0xE021",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Games",
        "Games"
    },
    {
        0xE90E,
        "0xE90E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Gavel",
        "Gavel"
    },
    {
        0xE155,
        "0xE155",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Gesture",
        "Gesture"
    },
    {
        0xE884,
        "0xE884",
        IconFontFamily::Material,
        "Material",
        "MatIcon::GetApp",
        "Get App"
    },
    {
        0xE908,
        "0xE908",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Gif",
        "Gif"
    },
    {
        0xEB45,
        "0xEB45",
        IconFontFamily::Material,
        "Material",
        "MatIcon::GolfCourse",
        "Golf Course"
    },
    {
        0xE1B3,
        "0xE1B3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::GpsFixed",
        "Gps Fixed"
    },
    {
        0xE1B4,
        "0xE1B4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::GpsNotFixed",
        "Gps Not Fixed"
    },
    {
        0xE1B5,
        "0xE1B5",
        IconFontFamily::Material,
        "Material",
        "MatIcon::GpsOff",
        "Gps Off"
    },
    {
        0xE885,
        "0xE885",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Grade",
        "Grade"
    },
    {
        0xE3E9,
        "0xE3E9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Gradient",
        "Gradient"
    },
    {
        0xE3EA,
        "0xE3EA",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Grain",
        "Grain"
    },
    {
        0xE1B8,
        "0xE1B8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::GraphicEq",
        "Graphic Eq"
    },
    {
        0xE3EB,
        "0xE3EB",
        IconFontFamily::Material,
        "Material",
        "MatIcon::GridOff",
        "Grid Off"
    },
    {
        0xE3EC,
        "0xE3EC",
        IconFontFamily::Material,
        "Material",
        "MatIcon::GridOn",
        "Grid On"
    },
    {
        0xE7EF,
        "0xE7EF",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Group",
        "Group"
    },
    {
        0xE7F0,
        "0xE7F0",
        IconFontFamily::Material,
        "Material",
        "MatIcon::GroupAdd",
        "Group Add"
    },
    {
        0xE886,
        "0xE886",
        IconFontFamily::Material,
        "Material",
        "MatIcon::GroupWork",
        "Group Work"
    },
    {
        0xE052,
        "0xE052",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Hd",
        "Hd"
    },
    {
        0xE3ED,
        "0xE3ED",
        IconFontFamily::Material,
        "Material",
        "MatIcon::HdrOff",
        "Hdr Off"
    },
    {
        0xE3EE,
        "0xE3EE",
        IconFontFamily::Material,
        "Material",
        "MatIcon::HdrOn",
        "Hdr On"
    },
    {
        0xE3F1,
        "0xE3F1",
        IconFontFamily::Material,
        "Material",
        "MatIcon::HdrStrong",
        "Hdr Strong"
    },
    {
        0xE3F2,
        "0xE3F2",
        IconFontFamily::Material,
        "Material",
        "MatIcon::HdrWeak",
        "Hdr Weak"
    },
    {
        0xE310,
        "0xE310",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Headset",
        "Headset"
    },
    {
        0xE311,
        "0xE311",
        IconFontFamily::Material,
        "Material",
        "MatIcon::HeadsetMic",
        "Headset Mic"
    },
    {
        0xE3F3,
        "0xE3F3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Healing",
        "Healing"
    },
    {
        0xE023,
        "0xE023",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Hearing",
        "Hearing"
    },
    {
        0xE887,
        "0xE887",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Help",
        "Help"
    },
    {
        0xE8FD,
        "0xE8FD",
        IconFontFamily::Material,
        "Material",
        "MatIcon::HelpOutline",
        "Help Outline"
    },
    {
        0xE024,
        "0xE024",
        IconFontFamily::Material,
        "Material",
        "MatIcon::HighQuality",
        "High Quality"
    },
    {
        0xE25F,
        "0xE25F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Highlight",
        "Highlight"
    },
    {
        0xE888,
        "0xE888",
        IconFontFamily::Material,
        "Material",
        "MatIcon::HighlightOff",
        "Highlight Off"
    },
    {
        0xE889,
        "0xE889",
        IconFontFamily::Material,
        "Material",
        "MatIcon::History",
        "History"
    },
    {
        0xE88A,
        "0xE88A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Home",
        "Home"
    },
    {
        0xEB46,
        "0xEB46",
        IconFontFamily::Material,
        "Material",
        "MatIcon::HotTub",
        "Hot Tub"
    },
    {
        0xE53A,
        "0xE53A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Hotel",
        "Hotel"
    },
    {
        0xE88B,
        "0xE88B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::HourglassEmpty",
        "Hourglass Empty"
    },
    {
        0xE88C,
        "0xE88C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::HourglassFull",
        "Hourglass Full"
    },
    {
        0xE902,
        "0xE902",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Http",
        "Http"
    },
    {
        0xE88D,
        "0xE88D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Https",
        "Https"
    },
    {
        0xE3F4,
        "0xE3F4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Image",
        "Image"
    },
    {
        0xE3F5,
        "0xE3F5",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ImageAspectRatio",
        "Image Aspect Ratio"
    },
    {
        0xE0E0,
        "0xE0E0",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ImportContacts",
        "Import Contacts"
    },
    {
        0xE0C3,
        "0xE0C3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ImportExport",
        "Import Export"
    },
    {
        0xE912,
        "0xE912",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ImportantDevices",
        "Important Devices"
    },
    {
        0xE156,
        "0xE156",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Inbox",
        "Inbox"
    },
    {
        0xE909,
        "0xE909",
        IconFontFamily::Material,
        "Material",
        "MatIcon::IndeterminateCheckBox",
        "Indeterminate Check Box"
    },
    {
        0xE88E,
        "0xE88E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Info",
        "Info"
    },
    {
        0xE88F,
        "0xE88F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::InfoOutline",
        "Info Outline"
    },
    {
        0xE890,
        "0xE890",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Input",
        "Input"
    },
    {
        0xE24B,
        "0xE24B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::InsertChart",
        "Insert Chart"
    },
    {
        0xE24C,
        "0xE24C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::InsertComment",
        "Insert Comment"
    },
    {
        0xE24D,
        "0xE24D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::InsertDriveFile",
        "Insert Drive File"
    },
    {
        0xE24E,
        "0xE24E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::InsertEmoticon",
        "Insert Emoticon"
    },
    {
        0xE24F,
        "0xE24F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::InsertInvitation",
        "Insert Invitation"
    },
    {
        0xE250,
        "0xE250",
        IconFontFamily::Material,
        "Material",
        "MatIcon::InsertLink",
        "Insert Link"
    },
    {
        0xE251,
        "0xE251",
        IconFontFamily::Material,
        "Material",
        "MatIcon::InsertPhoto",
        "Insert Photo"
    },
    {
        0xE891,
        "0xE891",
        IconFontFamily::Material,
        "Material",
        "MatIcon::InvertColors",
        "Invert Colors"
    },
    {
        0xE0C4,
        "0xE0C4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::InvertColorsOff",
        "Invert Colors Off"
    },
    {
        0xE3F6,
        "0xE3F6",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Iso",
        "Iso"
    },
    {
        0xE312,
        "0xE312",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Keyboard",
        "Keyboard"
    },
    {
        0xE313,
        "0xE313",
        IconFontFamily::Material,
        "Material",
        "MatIcon::KeyboardArrowDown",
        "Keyboard Arrow Down"
    },
    {
        0xE314,
        "0xE314",
        IconFontFamily::Material,
        "Material",
        "MatIcon::KeyboardArrowLeft",
        "Keyboard Arrow Left"
    },
    {
        0xE315,
        "0xE315",
        IconFontFamily::Material,
        "Material",
        "MatIcon::KeyboardArrowRight",
        "Keyboard Arrow Right"
    },
    {
        0xE316,
        "0xE316",
        IconFontFamily::Material,
        "Material",
        "MatIcon::KeyboardArrowUp",
        "Keyboard Arrow Up"
    },
    {
        0xE317,
        "0xE317",
        IconFontFamily::Material,
        "Material",
        "MatIcon::KeyboardBackspace",
        "Keyboard Backspace"
    },
    {
        0xE318,
        "0xE318",
        IconFontFamily::Material,
        "Material",
        "MatIcon::KeyboardCapslock",
        "Keyboard Capslock"
    },
    {
        0xE31A,
        "0xE31A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::KeyboardHide",
        "Keyboard Hide"
    },
    {
        0xE31B,
        "0xE31B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::KeyboardReturn",
        "Keyboard Return"
    },
    {
        0xE31C,
        "0xE31C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::KeyboardTab",
        "Keyboard Tab"
    },
    {
        0xE31D,
        "0xE31D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::KeyboardVoice",
        "Keyboard Voice"
    },
    {
        0xEB47,
        "0xEB47",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Kitchen",
        "Kitchen"
    },
    {
        0xE892,
        "0xE892",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Label",
        "Label"
    },
    {
        0xE893,
        "0xE893",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LabelOutline",
        "Label Outline"
    },
    {
        0xE3F7,
        "0xE3F7",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Landscape",
        "Landscape"
    },
    {
        0xE894,
        "0xE894",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Language",
        "Language"
    },
    {
        0xE31E,
        "0xE31E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Laptop",
        "Laptop"
    },
    {
        0xE31F,
        "0xE31F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LaptopChromebook",
        "Laptop Chromebook"
    },
    {
        0xE320,
        "0xE320",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LaptopMac",
        "Laptop Mac"
    },
    {
        0xE321,
        "0xE321",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LaptopWindows",
        "Laptop Windows"
    },
    {
        0xE5DD,
        "0xE5DD",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LastPage",
        "Last Page"
    },
    {
        0xE895,
        "0xE895",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Launch",
        "Launch"
    },
    {
        0xE53B,
        "0xE53B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Layers",
        "Layers"
    },
    {
        0xE53C,
        "0xE53C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LayersClear",
        "Layers Clear"
    },
    {
        0xE3F8,
        "0xE3F8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LeakAdd",
        "Leak Add"
    },
    {
        0xE3F9,
        "0xE3F9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LeakRemove",
        "Leak Remove"
    },
    {
        0xE3FA,
        "0xE3FA",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Lens",
        "Lens"
    },
    {
        0xE02E,
        "0xE02E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LibraryAdd",
        "Library Add"
    },
    {
        0xE02F,
        "0xE02F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LibraryBooks",
        "Library Books"
    },
    {
        0xE030,
        "0xE030",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LibraryMusic",
        "Library Music"
    },
    {
        0xE90F,
        "0xE90F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LightbulbOutline",
        "Lightbulb Outline"
    },
    {
        0xE919,
        "0xE919",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LineStyle",
        "Line Style"
    },
    {
        0xE91A,
        "0xE91A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LineWeight",
        "Line Weight"
    },
    {
        0xE260,
        "0xE260",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LinearScale",
        "Linear Scale"
    },
    {
        0xE157,
        "0xE157",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Link",
        "Link"
    },
    {
        0xE438,
        "0xE438",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LinkedCamera",
        "Linked Camera"
    },
    {
        0xE896,
        "0xE896",
        IconFontFamily::Material,
        "Material",
        "MatIcon::List",
        "List"
    },
    {
        0xE0C6,
        "0xE0C6",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LiveHelp",
        "Live Help"
    },
    {
        0xE639,
        "0xE639",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LiveTv",
        "Live Tv"
    },
    {
        0xE53F,
        "0xE53F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalActivity",
        "Local Activity"
    },
    {
        0xE53D,
        "0xE53D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalAirport",
        "Local Airport"
    },
    {
        0xE53E,
        "0xE53E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalAtm",
        "Local Atm"
    },
    {
        0xE540,
        "0xE540",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalBar",
        "Local Bar"
    },
    {
        0xE541,
        "0xE541",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalCafe",
        "Local Cafe"
    },
    {
        0xE542,
        "0xE542",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalCarWash",
        "Local Car Wash"
    },
    {
        0xE543,
        "0xE543",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalConvenienceStore",
        "Local Convenience Store"
    },
    {
        0xE556,
        "0xE556",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalDining",
        "Local Dining"
    },
    {
        0xE544,
        "0xE544",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalDrink",
        "Local Drink"
    },
    {
        0xE545,
        "0xE545",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalFlorist",
        "Local Florist"
    },
    {
        0xE546,
        "0xE546",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalGasStation",
        "Local Gas Station"
    },
    {
        0xE547,
        "0xE547",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalGroceryStore",
        "Local Grocery Store"
    },
    {
        0xE548,
        "0xE548",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalHospital",
        "Local Hospital"
    },
    {
        0xE549,
        "0xE549",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalHotel",
        "Local Hotel"
    },
    {
        0xE54A,
        "0xE54A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalLaundryService",
        "Local Laundry Service"
    },
    {
        0xE54B,
        "0xE54B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalLibrary",
        "Local Library"
    },
    {
        0xE54C,
        "0xE54C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalMall",
        "Local Mall"
    },
    {
        0xE54D,
        "0xE54D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalMovies",
        "Local Movies"
    },
    {
        0xE54E,
        "0xE54E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalOffer",
        "Local Offer"
    },
    {
        0xE54F,
        "0xE54F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalParking",
        "Local Parking"
    },
    {
        0xE550,
        "0xE550",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalPharmacy",
        "Local Pharmacy"
    },
    {
        0xE551,
        "0xE551",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalPhone",
        "Local Phone"
    },
    {
        0xE552,
        "0xE552",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalPizza",
        "Local Pizza"
    },
    {
        0xE553,
        "0xE553",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalPlay",
        "Local Play"
    },
    {
        0xE554,
        "0xE554",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalPostOffice",
        "Local Post Office"
    },
    {
        0xE555,
        "0xE555",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalPrintshop",
        "Local Printshop"
    },
    {
        0xE557,
        "0xE557",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalSee",
        "Local See"
    },
    {
        0xE558,
        "0xE558",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalShipping",
        "Local Shipping"
    },
    {
        0xE559,
        "0xE559",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocalTaxi",
        "Local Taxi"
    },
    {
        0xE7F1,
        "0xE7F1",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocationCity",
        "Location City"
    },
    {
        0xE1B6,
        "0xE1B6",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocationDisabled",
        "Location Disabled"
    },
    {
        0xE0C7,
        "0xE0C7",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocationOff",
        "Location Off"
    },
    {
        0xE0C8,
        "0xE0C8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocationOn",
        "Location On"
    },
    {
        0xE1B7,
        "0xE1B7",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LocationSearching",
        "Location Searching"
    },
    {
        0xE897,
        "0xE897",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Lock",
        "Lock"
    },
    {
        0xE898,
        "0xE898",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LockOpen",
        "Lock Open"
    },
    {
        0xE899,
        "0xE899",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LockOutline",
        "Lock Outline"
    },
    {
        0xE3FC,
        "0xE3FC",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Looks",
        "Looks"
    },
    {
        0xE3FB,
        "0xE3FB",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Looks_3",
        "Looks 3"
    },
    {
        0xE3FD,
        "0xE3FD",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Looks_4",
        "Looks 4"
    },
    {
        0xE3FE,
        "0xE3FE",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Looks_5",
        "Looks 5"
    },
    {
        0xE3FF,
        "0xE3FF",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Looks_6",
        "Looks 6"
    },
    {
        0xE400,
        "0xE400",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LooksOne",
        "Looks One"
    },
    {
        0xE401,
        "0xE401",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LooksTwo",
        "Looks Two"
    },
    {
        0xE028,
        "0xE028",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Loop",
        "Loop"
    },
    {
        0xE402,
        "0xE402",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Loupe",
        "Loupe"
    },
    {
        0xE16D,
        "0xE16D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::LowPriority",
        "Low Priority"
    },
    {
        0xE89A,
        "0xE89A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Loyalty",
        "Loyalty"
    },
    {
        0xE158,
        "0xE158",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Mail",
        "Mail"
    },
    {
        0xE0E1,
        "0xE0E1",
        IconFontFamily::Material,
        "Material",
        "MatIcon::MailOutline",
        "Mail Outline"
    },
    {
        0xE55B,
        "0xE55B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Map",
        "Map"
    },
    {
        0xE159,
        "0xE159",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Markunread",
        "Markunread"
    },
    {
        0xE89B,
        "0xE89B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::MarkunreadMailbox",
        "Markunread Mailbox"
    },
    {
        0xE322,
        "0xE322",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Memory",
        "Memory"
    },
    {
        0xE5D2,
        "0xE5D2",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Menu",
        "Menu"
    },
    {
        0xE252,
        "0xE252",
        IconFontFamily::Material,
        "Material",
        "MatIcon::MergeType",
        "Merge Type"
    },
    {
        0xE0C9,
        "0xE0C9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Message",
        "Message"
    },
    {
        0xE029,
        "0xE029",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Mic",
        "Mic"
    },
    {
        0xE02A,
        "0xE02A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::MicNone",
        "Mic None"
    },
    {
        0xE02B,
        "0xE02B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::MicOff",
        "Mic Off"
    },
    {
        0xE618,
        "0xE618",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Mms",
        "Mms"
    },
    {
        0xE253,
        "0xE253",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ModeComment",
        "Mode Comment"
    },
    {
        0xE254,
        "0xE254",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ModeEdit",
        "Mode Edit"
    },
    {
        0xE263,
        "0xE263",
        IconFontFamily::Material,
        "Material",
        "MatIcon::MonetizationOn",
        "Monetization On"
    },
    {
        0xE25C,
        "0xE25C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::MoneyOff",
        "Money Off"
    },
    {
        0xE403,
        "0xE403",
        IconFontFamily::Material,
        "Material",
        "MatIcon::MonochromePhotos",
        "Monochrome Photos"
    },
    {
        0xE7F2,
        "0xE7F2",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Mood",
        "Mood"
    },
    {
        0xE7F3,
        "0xE7F3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::MoodBad",
        "Mood Bad"
    },
    {
        0xE619,
        "0xE619",
        IconFontFamily::Material,
        "Material",
        "MatIcon::More",
        "More"
    },
    {
        0xE5D3,
        "0xE5D3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::MoreHoriz",
        "More Horiz"
    },
    {
        0xE5D4,
        "0xE5D4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::MoreVert",
        "More Vert"
    },
    {
        0xE91B,
        "0xE91B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Motorcycle",
        "Motorcycle"
    },
    {
        0xE323,
        "0xE323",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Mouse",
        "Mouse"
    },
    {
        0xE168,
        "0xE168",
        IconFontFamily::Material,
        "Material",
        "MatIcon::MoveToInbox",
        "Move To Inbox"
    },
    {
        0xE02C,
        "0xE02C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Movie",
        "Movie"
    },
    {
        0xE404,
        "0xE404",
        IconFontFamily::Material,
        "Material",
        "MatIcon::MovieCreation",
        "Movie Creation"
    },
    {
        0xE43A,
        "0xE43A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::MovieFilter",
        "Movie Filter"
    },
    {
        0xE6DF,
        "0xE6DF",
        IconFontFamily::Material,
        "Material",
        "MatIcon::MultilineChart",
        "Multiline Chart"
    },
    {
        0xE405,
        "0xE405",
        IconFontFamily::Material,
        "Material",
        "MatIcon::MusicNote",
        "Music Note"
    },
    {
        0xE063,
        "0xE063",
        IconFontFamily::Material,
        "Material",
        "MatIcon::MusicVideo",
        "Music Video"
    },
    {
        0xE55C,
        "0xE55C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::MyLocation",
        "My Location"
    },
    {
        0xE406,
        "0xE406",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Nature",
        "Nature"
    },
    {
        0xE407,
        "0xE407",
        IconFontFamily::Material,
        "Material",
        "MatIcon::NaturePeople",
        "Nature People"
    },
    {
        0xE408,
        "0xE408",
        IconFontFamily::Material,
        "Material",
        "MatIcon::NavigateBefore",
        "Navigate Before"
    },
    {
        0xE409,
        "0xE409",
        IconFontFamily::Material,
        "Material",
        "MatIcon::NavigateNext",
        "Navigate Next"
    },
    {
        0xE55D,
        "0xE55D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Navigation",
        "Navigation"
    },
    {
        0xE569,
        "0xE569",
        IconFontFamily::Material,
        "Material",
        "MatIcon::NearMe",
        "Near Me"
    },
    {
        0xE1B9,
        "0xE1B9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::NetworkCell",
        "Network Cell"
    },
    {
        0xE640,
        "0xE640",
        IconFontFamily::Material,
        "Material",
        "MatIcon::NetworkCheck",
        "Network Check"
    },
    {
        0xE61A,
        "0xE61A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::NetworkLocked",
        "Network Locked"
    },
    {
        0xE1BA,
        "0xE1BA",
        IconFontFamily::Material,
        "Material",
        "MatIcon::NetworkWifi",
        "Network Wifi"
    },
    {
        0xE031,
        "0xE031",
        IconFontFamily::Material,
        "Material",
        "MatIcon::NewReleases",
        "New Releases"
    },
    {
        0xE16A,
        "0xE16A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::NextWeek",
        "Next Week"
    },
    {
        0xE1BB,
        "0xE1BB",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Nfc",
        "Nfc"
    },
    {
        0xE641,
        "0xE641",
        IconFontFamily::Material,
        "Material",
        "MatIcon::NoEncryption",
        "No Encryption"
    },
    {
        0xE0CC,
        "0xE0CC",
        IconFontFamily::Material,
        "Material",
        "MatIcon::NoSim",
        "No Sim"
    },
    {
        0xE033,
        "0xE033",
        IconFontFamily::Material,
        "Material",
        "MatIcon::NotInterested",
        "Not Interested"
    },
    {
        0xE06F,
        "0xE06F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Note",
        "Note"
    },
    {
        0xE89C,
        "0xE89C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::NoteAdd",
        "Note Add"
    },
    {
        0xE7F4,
        "0xE7F4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Notifications",
        "Notifications"
    },
    {
        0xE7F7,
        "0xE7F7",
        IconFontFamily::Material,
        "Material",
        "MatIcon::NotificationsActive",
        "Notifications Active"
    },
    {
        0xE7F5,
        "0xE7F5",
        IconFontFamily::Material,
        "Material",
        "MatIcon::NotificationsNone",
        "Notifications None"
    },
    {
        0xE7F6,
        "0xE7F6",
        IconFontFamily::Material,
        "Material",
        "MatIcon::NotificationsOff",
        "Notifications Off"
    },
    {
        0xE7F8,
        "0xE7F8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::NotificationsPaused",
        "Notifications Paused"
    },
    {
        0xE90A,
        "0xE90A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::OfflinePin",
        "Offline Pin"
    },
    {
        0xE63A,
        "0xE63A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::OndemandVideo",
        "Ondemand Video"
    },
    {
        0xE91C,
        "0xE91C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Opacity",
        "Opacity"
    },
    {
        0xE89D,
        "0xE89D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::OpenInBrowser",
        "Open In Browser"
    },
    {
        0xE89E,
        "0xE89E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::OpenInNew",
        "Open In New"
    },
    {
        0xE89F,
        "0xE89F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::OpenWith",
        "Open With"
    },
    {
        0xE7F9,
        "0xE7F9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Pages",
        "Pages"
    },
    {
        0xE8A0,
        "0xE8A0",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Pageview",
        "Pageview"
    },
    {
        0xE40A,
        "0xE40A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Palette",
        "Palette"
    },
    {
        0xE925,
        "0xE925",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PanTool",
        "Pan Tool"
    },
    {
        0xE40B,
        "0xE40B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Panorama",
        "Panorama"
    },
    {
        0xE40C,
        "0xE40C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PanoramaFishEye",
        "Panorama Fish Eye"
    },
    {
        0xE40D,
        "0xE40D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PanoramaHorizontal",
        "Panorama Horizontal"
    },
    {
        0xE40E,
        "0xE40E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PanoramaVertical",
        "Panorama Vertical"
    },
    {
        0xE40F,
        "0xE40F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PanoramaWideAngle",
        "Panorama Wide Angle"
    },
    {
        0xE7FA,
        "0xE7FA",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PartyMode",
        "Party Mode"
    },
    {
        0xE034,
        "0xE034",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Pause",
        "Pause"
    },
    {
        0xE035,
        "0xE035",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PauseCircleFilled",
        "Pause Circle Filled"
    },
    {
        0xE036,
        "0xE036",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PauseCircleOutline",
        "Pause Circle Outline"
    },
    {
        0xE8A1,
        "0xE8A1",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Payment",
        "Payment"
    },
    {
        0xE7FB,
        "0xE7FB",
        IconFontFamily::Material,
        "Material",
        "MatIcon::People",
        "People"
    },
    {
        0xE7FC,
        "0xE7FC",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PeopleOutline",
        "People Outline"
    },
    {
        0xE8A2,
        "0xE8A2",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PermCameraMic",
        "Perm Camera Mic"
    },
    {
        0xE8A3,
        "0xE8A3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PermContactCalendar",
        "Perm Contact Calendar"
    },
    {
        0xE8A4,
        "0xE8A4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PermDataSetting",
        "Perm Data Setting"
    },
    {
        0xE8A5,
        "0xE8A5",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PermDeviceInformation",
        "Perm Device Information"
    },
    {
        0xE8A6,
        "0xE8A6",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PermIdentity",
        "Perm Identity"
    },
    {
        0xE8A7,
        "0xE8A7",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PermMedia",
        "Perm Media"
    },
    {
        0xE8A8,
        "0xE8A8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PermPhoneMsg",
        "Perm Phone Msg"
    },
    {
        0xE8A9,
        "0xE8A9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PermScanWifi",
        "Perm Scan Wifi"
    },
    {
        0xE7FD,
        "0xE7FD",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Person",
        "Person"
    },
    {
        0xE7FE,
        "0xE7FE",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PersonAdd",
        "Person Add"
    },
    {
        0xE7FF,
        "0xE7FF",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PersonOutline",
        "Person Outline"
    },
    {
        0xE55A,
        "0xE55A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PersonPin",
        "Person Pin"
    },
    {
        0xE56A,
        "0xE56A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PersonPinCircle",
        "Person Pin Circle"
    },
    {
        0xE63B,
        "0xE63B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PersonalVideo",
        "Personal Video"
    },
    {
        0xE91D,
        "0xE91D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Pets",
        "Pets"
    },
    {
        0xE0CD,
        "0xE0CD",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Phone",
        "Phone"
    },
    {
        0xE324,
        "0xE324",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PhoneAndroid",
        "Phone Android"
    },
    {
        0xE61B,
        "0xE61B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PhoneBluetoothSpeaker",
        "Phone Bluetooth Speaker"
    },
    {
        0xE61C,
        "0xE61C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PhoneForwarded",
        "Phone Forwarded"
    },
    {
        0xE61D,
        "0xE61D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PhoneInTalk",
        "Phone In Talk"
    },
    {
        0xE325,
        "0xE325",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PhoneIphone",
        "Phone Iphone"
    },
    {
        0xE61E,
        "0xE61E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PhoneLocked",
        "Phone Locked"
    },
    {
        0xE61F,
        "0xE61F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PhoneMissed",
        "Phone Missed"
    },
    {
        0xE620,
        "0xE620",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PhonePaused",
        "Phone Paused"
    },
    {
        0xE326,
        "0xE326",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Phonelink",
        "Phonelink"
    },
    {
        0xE0DB,
        "0xE0DB",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PhonelinkErase",
        "Phonelink Erase"
    },
    {
        0xE0DC,
        "0xE0DC",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PhonelinkLock",
        "Phonelink Lock"
    },
    {
        0xE327,
        "0xE327",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PhonelinkOff",
        "Phonelink Off"
    },
    {
        0xE0DD,
        "0xE0DD",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PhonelinkRing",
        "Phonelink Ring"
    },
    {
        0xE0DE,
        "0xE0DE",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PhonelinkSetup",
        "Phonelink Setup"
    },
    {
        0xE410,
        "0xE410",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Photo",
        "Photo"
    },
    {
        0xE411,
        "0xE411",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PhotoAlbum",
        "Photo Album"
    },
    {
        0xE412,
        "0xE412",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PhotoCamera",
        "Photo Camera"
    },
    {
        0xE43B,
        "0xE43B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PhotoFilter",
        "Photo Filter"
    },
    {
        0xE413,
        "0xE413",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PhotoLibrary",
        "Photo Library"
    },
    {
        0xE432,
        "0xE432",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PhotoSizeSelectActual",
        "Photo Size Select Actual"
    },
    {
        0xE433,
        "0xE433",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PhotoSizeSelectLarge",
        "Photo Size Select Large"
    },
    {
        0xE434,
        "0xE434",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PhotoSizeSelectSmall",
        "Photo Size Select Small"
    },
    {
        0xE415,
        "0xE415",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PictureAsPdf",
        "Picture As Pdf"
    },
    {
        0xE8AA,
        "0xE8AA",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PictureInPicture",
        "Picture In Picture"
    },
    {
        0xE911,
        "0xE911",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PictureInPictureAlt",
        "Picture In Picture Alt"
    },
    {
        0xE6C4,
        "0xE6C4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PieChart",
        "Pie Chart"
    },
    {
        0xE6C5,
        "0xE6C5",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PieChartOutlined",
        "Pie Chart Outlined"
    },
    {
        0xE55E,
        "0xE55E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PinDrop",
        "Pin Drop"
    },
    {
        0xE55F,
        "0xE55F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Place",
        "Place"
    },
    {
        0xE037,
        "0xE037",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PlayArrow",
        "Play Arrow"
    },
    {
        0xE038,
        "0xE038",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PlayCircleFilled",
        "Play Circle Filled"
    },
    {
        0xE039,
        "0xE039",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PlayCircleOutline",
        "Play Circle Outline"
    },
    {
        0xE906,
        "0xE906",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PlayForWork",
        "Play For Work"
    },
    {
        0xE03B,
        "0xE03B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PlaylistAdd",
        "Playlist Add"
    },
    {
        0xE065,
        "0xE065",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PlaylistAddCheck",
        "Playlist Add Check"
    },
    {
        0xE05F,
        "0xE05F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PlaylistPlay",
        "Playlist Play"
    },
    {
        0xE800,
        "0xE800",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PlusOne",
        "Plus One"
    },
    {
        0xE801,
        "0xE801",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Poll",
        "Poll"
    },
    {
        0xE8AB,
        "0xE8AB",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Polymer",
        "Polymer"
    },
    {
        0xEB48,
        "0xEB48",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Pool",
        "Pool"
    },
    {
        0xE0CE,
        "0xE0CE",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PortableWifiOff",
        "Portable Wifi Off"
    },
    {
        0xE416,
        "0xE416",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Portrait",
        "Portrait"
    },
    {
        0xE63C,
        "0xE63C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Power",
        "Power"
    },
    {
        0xE336,
        "0xE336",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PowerInput",
        "Power Input"
    },
    {
        0xE8AC,
        "0xE8AC",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PowerSettingsNew",
        "Power Settings New"
    },
    {
        0xE91E,
        "0xE91E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PregnantWoman",
        "Pregnant Woman"
    },
    {
        0xE0DF,
        "0xE0DF",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PresentToAll",
        "Present To All"
    },
    {
        0xE8AD,
        "0xE8AD",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Print",
        "Print"
    },
    {
        0xE645,
        "0xE645",
        IconFontFamily::Material,
        "Material",
        "MatIcon::PriorityHigh",
        "Priority High"
    },
    {
        0xE80B,
        "0xE80B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Public",
        "Public"
    },
    {
        0xE255,
        "0xE255",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Publish",
        "Publish"
    },
    {
        0xE8AE,
        "0xE8AE",
        IconFontFamily::Material,
        "Material",
        "MatIcon::QueryBuilder",
        "Query Builder"
    },
    {
        0xE8AF,
        "0xE8AF",
        IconFontFamily::Material,
        "Material",
        "MatIcon::QuestionAnswer",
        "Question Answer"
    },
    {
        0xE03C,
        "0xE03C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Queue",
        "Queue"
    },
    {
        0xE03D,
        "0xE03D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::QueueMusic",
        "Queue Music"
    },
    {
        0xE066,
        "0xE066",
        IconFontFamily::Material,
        "Material",
        "MatIcon::QueuePlayNext",
        "Queue Play Next"
    },
    {
        0xE03E,
        "0xE03E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Radio",
        "Radio"
    },
    {
        0xE837,
        "0xE837",
        IconFontFamily::Material,
        "Material",
        "MatIcon::RadioButtonChecked",
        "Radio Button Checked"
    },
    {
        0xE836,
        "0xE836",
        IconFontFamily::Material,
        "Material",
        "MatIcon::RadioButtonUnchecked",
        "Radio Button Unchecked"
    },
    {
        0xE560,
        "0xE560",
        IconFontFamily::Material,
        "Material",
        "MatIcon::RateReview",
        "Rate Review"
    },
    {
        0xE8B0,
        "0xE8B0",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Receipt",
        "Receipt"
    },
    {
        0xE03F,
        "0xE03F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::RecentActors",
        "Recent Actors"
    },
    {
        0xE91F,
        "0xE91F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::RecordVoiceOver",
        "Record Voice Over"
    },
    {
        0xE8B1,
        "0xE8B1",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Redeem",
        "Redeem"
    },
    {
        0xE15A,
        "0xE15A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Redo",
        "Redo"
    },
    {
        0xE5D5,
        "0xE5D5",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Refresh",
        "Refresh"
    },
    {
        0xE15B,
        "0xE15B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Remove",
        "Remove"
    },
    {
        0xE15C,
        "0xE15C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::RemoveCircle",
        "Remove Circle"
    },
    {
        0xE15D,
        "0xE15D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::RemoveCircleOutline",
        "Remove Circle Outline"
    },
    {
        0xE067,
        "0xE067",
        IconFontFamily::Material,
        "Material",
        "MatIcon::RemoveFromQueue",
        "Remove From Queue"
    },
    {
        0xE417,
        "0xE417",
        IconFontFamily::Material,
        "Material",
        "MatIcon::RemoveRedEye",
        "Remove Red Eye"
    },
    {
        0xE928,
        "0xE928",
        IconFontFamily::Material,
        "Material",
        "MatIcon::RemoveShoppingCart",
        "Remove Shopping Cart"
    },
    {
        0xE8FE,
        "0xE8FE",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Reorder",
        "Reorder"
    },
    {
        0xE040,
        "0xE040",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Repeat",
        "Repeat"
    },
    {
        0xE041,
        "0xE041",
        IconFontFamily::Material,
        "Material",
        "MatIcon::RepeatOne",
        "Repeat One"
    },
    {
        0xE042,
        "0xE042",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Replay",
        "Replay"
    },
    {
        0xE059,
        "0xE059",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Replay_10",
        "Replay 10"
    },
    {
        0xE05A,
        "0xE05A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Replay_30",
        "Replay 30"
    },
    {
        0xE05B,
        "0xE05B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Replay_5",
        "Replay 5"
    },
    {
        0xE15E,
        "0xE15E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Reply",
        "Reply"
    },
    {
        0xE15F,
        "0xE15F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ReplyAll",
        "Reply All"
    },
    {
        0xE160,
        "0xE160",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Report",
        "Report"
    },
    {
        0xE8B2,
        "0xE8B2",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ReportProblem",
        "Report Problem"
    },
    {
        0xE56C,
        "0xE56C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Restaurant",
        "Restaurant"
    },
    {
        0xE561,
        "0xE561",
        IconFontFamily::Material,
        "Material",
        "MatIcon::RestaurantMenu",
        "Restaurant Menu"
    },
    {
        0xE8B3,
        "0xE8B3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Restore",
        "Restore"
    },
    {
        0xE929,
        "0xE929",
        IconFontFamily::Material,
        "Material",
        "MatIcon::RestorePage",
        "Restore Page"
    },
    {
        0xE0D1,
        "0xE0D1",
        IconFontFamily::Material,
        "Material",
        "MatIcon::RingVolume",
        "Ring Volume"
    },
    {
        0xE8B4,
        "0xE8B4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Room",
        "Room"
    },
    {
        0xEB49,
        "0xEB49",
        IconFontFamily::Material,
        "Material",
        "MatIcon::RoomService",
        "Room Service"
    },
    {
        0xE418,
        "0xE418",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Rotate_90DegreesCcw",
        "Rotate 90 Degrees Ccw"
    },
    {
        0xE419,
        "0xE419",
        IconFontFamily::Material,
        "Material",
        "MatIcon::RotateLeft",
        "Rotate Left"
    },
    {
        0xE41A,
        "0xE41A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::RotateRight",
        "Rotate Right"
    },
    {
        0xE920,
        "0xE920",
        IconFontFamily::Material,
        "Material",
        "MatIcon::RoundedCorner",
        "Rounded Corner"
    },
    {
        0xE328,
        "0xE328",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Router",
        "Router"
    },
    {
        0xE921,
        "0xE921",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Rowing",
        "Rowing"
    },
    {
        0xE0E5,
        "0xE0E5",
        IconFontFamily::Material,
        "Material",
        "MatIcon::RssFeed",
        "Rss Feed"
    },
    {
        0xE642,
        "0xE642",
        IconFontFamily::Material,
        "Material",
        "MatIcon::RvHookup",
        "Rv Hookup"
    },
    {
        0xE562,
        "0xE562",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Satellite",
        "Satellite"
    },
    {
        0xE161,
        "0xE161",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Save",
        "Save"
    },
    {
        0xE329,
        "0xE329",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Scanner",
        "Scanner"
    },
    {
        0xE8B5,
        "0xE8B5",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Schedule",
        "Schedule"
    },
    {
        0xE80C,
        "0xE80C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::School",
        "School"
    },
    {
        0xE1BE,
        "0xE1BE",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ScreenLockLandscape",
        "Screen Lock Landscape"
    },
    {
        0xE1BF,
        "0xE1BF",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ScreenLockPortrait",
        "Screen Lock Portrait"
    },
    {
        0xE1C0,
        "0xE1C0",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ScreenLockRotation",
        "Screen Lock Rotation"
    },
    {
        0xE1C1,
        "0xE1C1",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ScreenRotation",
        "Screen Rotation"
    },
    {
        0xE0E2,
        "0xE0E2",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ScreenShare",
        "Screen Share"
    },
    {
        0xE623,
        "0xE623",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SdCard",
        "Sd Card"
    },
    {
        0xE1C2,
        "0xE1C2",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SdStorage",
        "Sd Storage"
    },
    {
        0xE8B6,
        "0xE8B6",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Search",
        "Search"
    },
    {
        0xE32A,
        "0xE32A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Security",
        "Security"
    },
    {
        0xE162,
        "0xE162",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SelectAll",
        "Select All"
    },
    {
        0xE163,
        "0xE163",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Send",
        "Send"
    },
    {
        0xE811,
        "0xE811",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SentimentDissatisfied",
        "Sentiment Dissatisfied"
    },
    {
        0xE812,
        "0xE812",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SentimentNeutral",
        "Sentiment Neutral"
    },
    {
        0xE813,
        "0xE813",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SentimentSatisfied",
        "Sentiment Satisfied"
    },
    {
        0xE814,
        "0xE814",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SentimentVeryDissatisfied",
        "Sentiment Very Dissatisfied"
    },
    {
        0xE815,
        "0xE815",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SentimentVerySatisfied",
        "Sentiment Very Satisfied"
    },
    {
        0xE8B8,
        "0xE8B8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Settings",
        "Settings"
    },
    {
        0xE8B9,
        "0xE8B9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SettingsApplications",
        "Settings Applications"
    },
    {
        0xE8BA,
        "0xE8BA",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SettingsBackupRestore",
        "Settings Backup Restore"
    },
    {
        0xE8BB,
        "0xE8BB",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SettingsBluetooth",
        "Settings Bluetooth"
    },
    {
        0xE8BD,
        "0xE8BD",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SettingsBrightness",
        "Settings Brightness"
    },
    {
        0xE8BC,
        "0xE8BC",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SettingsCell",
        "Settings Cell"
    },
    {
        0xE8BE,
        "0xE8BE",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SettingsEthernet",
        "Settings Ethernet"
    },
    {
        0xE8BF,
        "0xE8BF",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SettingsInputAntenna",
        "Settings Input Antenna"
    },
    {
        0xE8C0,
        "0xE8C0",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SettingsInputComponent",
        "Settings Input Component"
    },
    {
        0xE8C1,
        "0xE8C1",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SettingsInputComposite",
        "Settings Input Composite"
    },
    {
        0xE8C2,
        "0xE8C2",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SettingsInputHdmi",
        "Settings Input Hdmi"
    },
    {
        0xE8C3,
        "0xE8C3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SettingsInputSvideo",
        "Settings Input Svideo"
    },
    {
        0xE8C4,
        "0xE8C4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SettingsOverscan",
        "Settings Overscan"
    },
    {
        0xE8C5,
        "0xE8C5",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SettingsPhone",
        "Settings Phone"
    },
    {
        0xE8C6,
        "0xE8C6",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SettingsPower",
        "Settings Power"
    },
    {
        0xE8C7,
        "0xE8C7",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SettingsRemote",
        "Settings Remote"
    },
    {
        0xE1C3,
        "0xE1C3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SettingsSystemDaydream",
        "Settings System Daydream"
    },
    {
        0xE8C8,
        "0xE8C8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SettingsVoice",
        "Settings Voice"
    },
    {
        0xE80D,
        "0xE80D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Share",
        "Share"
    },
    {
        0xE8C9,
        "0xE8C9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Shop",
        "Shop"
    },
    {
        0xE8CA,
        "0xE8CA",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ShopTwo",
        "Shop Two"
    },
    {
        0xE8CB,
        "0xE8CB",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ShoppingBasket",
        "Shopping Basket"
    },
    {
        0xE8CC,
        "0xE8CC",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ShoppingCart",
        "Shopping Cart"
    },
    {
        0xE261,
        "0xE261",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ShortText",
        "Short Text"
    },
    {
        0xE6E1,
        "0xE6E1",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ShowChart",
        "Show Chart"
    },
    {
        0xE043,
        "0xE043",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Shuffle",
        "Shuffle"
    },
    {
        0xE1C8,
        "0xE1C8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SignalCellular_4Bar",
        "Signal Cellular 4 Bar"
    },
    {
        0xE1CD,
        "0xE1CD",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SignalCellularConnectedNoInternet",
        "Signal Cellular Connected No Internet"
    },
    {
        0xE1CE,
        "0xE1CE",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SignalCellularNoSim",
        "Signal Cellular No Sim"
    },
    {
        0xE1CF,
        "0xE1CF",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SignalCellularNull",
        "Signal Cellular Null"
    },
    {
        0xE1D0,
        "0xE1D0",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SignalCellularOff",
        "Signal Cellular Off"
    },
    {
        0xE1D8,
        "0xE1D8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SignalWifi_4Bar",
        "Signal Wifi 4 Bar"
    },
    {
        0xE1D9,
        "0xE1D9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SignalWifi_4BarLock",
        "Signal Wifi 4 BarLock"
    },
    {
        0xE1DA,
        "0xE1DA",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SignalWifiOff",
        "Signal Wifi Off"
    },
    {
        0xE32B,
        "0xE32B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SimCard",
        "Sim Card"
    },
    {
        0xE624,
        "0xE624",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SimCardAlert",
        "Sim Card Alert"
    },
    {
        0xE044,
        "0xE044",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SkipNext",
        "Skip Next"
    },
    {
        0xE045,
        "0xE045",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SkipPrevious",
        "Skip Previous"
    },
    {
        0xE41B,
        "0xE41B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Slideshow",
        "Slideshow"
    },
    {
        0xE068,
        "0xE068",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SlowMotionVideo",
        "Slow Motion Video"
    },
    {
        0xE32C,
        "0xE32C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Smartphone",
        "Smartphone"
    },
    {
        0xEB4A,
        "0xEB4A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SmokeFree",
        "Smoke Free"
    },
    {
        0xEB4B,
        "0xEB4B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SmokingRooms",
        "Smoking Rooms"
    },
    {
        0xE625,
        "0xE625",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Sms",
        "Sms"
    },
    {
        0xE626,
        "0xE626",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SmsFailed",
        "Sms Failed"
    },
    {
        0xE046,
        "0xE046",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Snooze",
        "Snooze"
    },
    {
        0xE164,
        "0xE164",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Sort",
        "Sort"
    },
    {
        0xE053,
        "0xE053",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SortByAlpha",
        "Sort By Alpha"
    },
    {
        0xEB4C,
        "0xEB4C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Spa",
        "Spa"
    },
    {
        0xE256,
        "0xE256",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SpaceBar",
        "Space Bar"
    },
    {
        0xE32D,
        "0xE32D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Speaker",
        "Speaker"
    },
    {
        0xE32E,
        "0xE32E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SpeakerGroup",
        "Speaker Group"
    },
    {
        0xE8CD,
        "0xE8CD",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SpeakerNotes",
        "Speaker Notes"
    },
    {
        0xE92A,
        "0xE92A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SpeakerNotesOff",
        "Speaker Notes Off"
    },
    {
        0xE0D2,
        "0xE0D2",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SpeakerPhone",
        "Speaker Phone"
    },
    {
        0xE8CE,
        "0xE8CE",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Spellcheck",
        "Spellcheck"
    },
    {
        0xE838,
        "0xE838",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Star",
        "Star"
    },
    {
        0xE83A,
        "0xE83A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::StarBorder",
        "Star Border"
    },
    {
        0xE839,
        "0xE839",
        IconFontFamily::Material,
        "Material",
        "MatIcon::StarHalf",
        "Star Half"
    },
    {
        0xE8D0,
        "0xE8D0",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Stars",
        "Stars"
    },
    {
        0xE0D3,
        "0xE0D3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::StayCurrentLandscape",
        "Stay Current Landscape"
    },
    {
        0xE0D4,
        "0xE0D4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::StayCurrentPortrait",
        "Stay Current Portrait"
    },
    {
        0xE0D5,
        "0xE0D5",
        IconFontFamily::Material,
        "Material",
        "MatIcon::StayPrimaryLandscape",
        "Stay Primary Landscape"
    },
    {
        0xE0D6,
        "0xE0D6",
        IconFontFamily::Material,
        "Material",
        "MatIcon::StayPrimaryPortrait",
        "Stay Primary Portrait"
    },
    {
        0xE047,
        "0xE047",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Stop",
        "Stop"
    },
    {
        0xE0E3,
        "0xE0E3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::StopScreenShare",
        "Stop Screen Share"
    },
    {
        0xE1DB,
        "0xE1DB",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Storage",
        "Storage"
    },
    {
        0xE8D1,
        "0xE8D1",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Store",
        "Store"
    },
    {
        0xE563,
        "0xE563",
        IconFontFamily::Material,
        "Material",
        "MatIcon::StoreMallDirectory",
        "Store Mall Directory"
    },
    {
        0xE41C,
        "0xE41C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Straighten",
        "Straighten"
    },
    {
        0xE56E,
        "0xE56E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Streetview",
        "Streetview"
    },
    {
        0xE257,
        "0xE257",
        IconFontFamily::Material,
        "Material",
        "MatIcon::StrikethroughS",
        "Strikethrough S"
    },
    {
        0xE41D,
        "0xE41D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Style",
        "Style"
    },
    {
        0xE5D9,
        "0xE5D9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SubdirectoryArrowLeft",
        "Subdirectory Arrow Left"
    },
    {
        0xE5DA,
        "0xE5DA",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SubdirectoryArrowRight",
        "Subdirectory Arrow Right"
    },
    {
        0xE8D2,
        "0xE8D2",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Subject",
        "Subject"
    },
    {
        0xE064,
        "0xE064",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Subscriptions",
        "Subscriptions"
    },
    {
        0xE048,
        "0xE048",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Subtitles",
        "Subtitles"
    },
    {
        0xE56F,
        "0xE56F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Subway",
        "Subway"
    },
    {
        0xE8D3,
        "0xE8D3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SupervisorAccount",
        "Supervisor Account"
    },
    {
        0xE049,
        "0xE049",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SurroundSound",
        "Surround Sound"
    },
    {
        0xE0D7,
        "0xE0D7",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SwapCalls",
        "Swap Calls"
    },
    {
        0xE8D4,
        "0xE8D4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SwapHoriz",
        "Swap Horiz"
    },
    {
        0xE8D5,
        "0xE8D5",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SwapVert",
        "Swap Vert"
    },
    {
        0xE8D6,
        "0xE8D6",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SwapVerticalCircle",
        "Swap Vertical Circle"
    },
    {
        0xE41E,
        "0xE41E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SwitchCamera",
        "Switch Camera"
    },
    {
        0xE41F,
        "0xE41F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SwitchVideo",
        "Switch Video"
    },
    {
        0xE627,
        "0xE627",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Sync",
        "Sync"
    },
    {
        0xE628,
        "0xE628",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SyncDisabled",
        "Sync Disabled"
    },
    {
        0xE629,
        "0xE629",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SyncProblem",
        "Sync Problem"
    },
    {
        0xE62A,
        "0xE62A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SystemUpdate",
        "System Update"
    },
    {
        0xE8D7,
        "0xE8D7",
        IconFontFamily::Material,
        "Material",
        "MatIcon::SystemUpdateAlt",
        "System Update Alt"
    },
    {
        0xE8D8,
        "0xE8D8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Tab",
        "Tab"
    },
    {
        0xE8D9,
        "0xE8D9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::TabUnselected",
        "Tab Unselected"
    },
    {
        0xE32F,
        "0xE32F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Tablet",
        "Tablet"
    },
    {
        0xE330,
        "0xE330",
        IconFontFamily::Material,
        "Material",
        "MatIcon::TabletAndroid",
        "Tablet Android"
    },
    {
        0xE331,
        "0xE331",
        IconFontFamily::Material,
        "Material",
        "MatIcon::TabletMac",
        "Tablet Mac"
    },
    {
        0xE420,
        "0xE420",
        IconFontFamily::Material,
        "Material",
        "MatIcon::TagFaces",
        "Tag Faces"
    },
    {
        0xE62B,
        "0xE62B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::TapAndPlay",
        "Tap And Play"
    },
    {
        0xE564,
        "0xE564",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Terrain",
        "Terrain"
    },
    {
        0xE262,
        "0xE262",
        IconFontFamily::Material,
        "Material",
        "MatIcon::TextFields",
        "Text Fields"
    },
    {
        0xE165,
        "0xE165",
        IconFontFamily::Material,
        "Material",
        "MatIcon::TextFormat",
        "Text Format"
    },
    {
        0xE0D8,
        "0xE0D8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Textsms",
        "Textsms"
    },
    {
        0xE421,
        "0xE421",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Texture",
        "Texture"
    },
    {
        0xE8DA,
        "0xE8DA",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Theaters",
        "Theaters"
    },
    {
        0xE8DB,
        "0xE8DB",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ThumbDown",
        "Thumb Down"
    },
    {
        0xE8DC,
        "0xE8DC",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ThumbUp",
        "Thumb Up"
    },
    {
        0xE8DD,
        "0xE8DD",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ThumbsUpDown",
        "Thumbs Up Down"
    },
    {
        0xE62C,
        "0xE62C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::TimeToLeave",
        "Time To Leave"
    },
    {
        0xE422,
        "0xE422",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Timelapse",
        "Timelapse"
    },
    {
        0xE922,
        "0xE922",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Timeline",
        "Timeline"
    },
    {
        0xE425,
        "0xE425",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Timer",
        "Timer"
    },
    {
        0xE423,
        "0xE423",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Timer_10",
        "Timer 10"
    },
    {
        0xE424,
        "0xE424",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Timer_3",
        "Timer 3"
    },
    {
        0xE426,
        "0xE426",
        IconFontFamily::Material,
        "Material",
        "MatIcon::TimerOff",
        "Timer Off"
    },
    {
        0xE264,
        "0xE264",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Title",
        "Title"
    },
    {
        0xE8DE,
        "0xE8DE",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Toc",
        "Toc"
    },
    {
        0xE8DF,
        "0xE8DF",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Today",
        "Today"
    },
    {
        0xE8E0,
        "0xE8E0",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Toll",
        "Toll"
    },
    {
        0xE427,
        "0xE427",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Tonality",
        "Tonality"
    },
    {
        0xE913,
        "0xE913",
        IconFontFamily::Material,
        "Material",
        "MatIcon::TouchApp",
        "Touch App"
    },
    {
        0xE332,
        "0xE332",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Toys",
        "Toys"
    },
    {
        0xE8E1,
        "0xE8E1",
        IconFontFamily::Material,
        "Material",
        "MatIcon::TrackChanges",
        "Track Changes"
    },
    {
        0xE565,
        "0xE565",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Traffic",
        "Traffic"
    },
    {
        0xE570,
        "0xE570",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Train",
        "Train"
    },
    {
        0xE571,
        "0xE571",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Tram",
        "Tram"
    },
    {
        0xE572,
        "0xE572",
        IconFontFamily::Material,
        "Material",
        "MatIcon::TransferWithinAStation",
        "Transfer Within A Station"
    },
    {
        0xE428,
        "0xE428",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Transform",
        "Transform"
    },
    {
        0xE8E2,
        "0xE8E2",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Translate",
        "Translate"
    },
    {
        0xE8E3,
        "0xE8E3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::TrendingDown",
        "Trending Down"
    },
    {
        0xE8E4,
        "0xE8E4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::TrendingFlat",
        "Trending Flat"
    },
    {
        0xE8E5,
        "0xE8E5",
        IconFontFamily::Material,
        "Material",
        "MatIcon::TrendingUp",
        "Trending Up"
    },
    {
        0xE429,
        "0xE429",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Tune",
        "Tune"
    },
    {
        0xE8E6,
        "0xE8E6",
        IconFontFamily::Material,
        "Material",
        "MatIcon::TurnedIn",
        "Turned In"
    },
    {
        0xE8E7,
        "0xE8E7",
        IconFontFamily::Material,
        "Material",
        "MatIcon::TurnedInNot",
        "Turned In Not"
    },
    {
        0xE333,
        "0xE333",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Tv",
        "Tv"
    },
    {
        0xE169,
        "0xE169",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Unarchive",
        "Unarchive"
    },
    {
        0xE166,
        "0xE166",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Undo",
        "Undo"
    },
    {
        0xE5D6,
        "0xE5D6",
        IconFontFamily::Material,
        "Material",
        "MatIcon::UnfoldLess",
        "Unfold Less"
    },
    {
        0xE5D7,
        "0xE5D7",
        IconFontFamily::Material,
        "Material",
        "MatIcon::UnfoldMore",
        "Unfold More"
    },
    {
        0xE923,
        "0xE923",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Update",
        "Update"
    },
    {
        0xE1E0,
        "0xE1E0",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Usb",
        "Usb"
    },
    {
        0xE8E8,
        "0xE8E8",
        IconFontFamily::Material,
        "Material",
        "MatIcon::VerifiedUser",
        "Verified User"
    },
    {
        0xE258,
        "0xE258",
        IconFontFamily::Material,
        "Material",
        "MatIcon::VerticalAlignBottom",
        "Vertical Align Bottom"
    },
    {
        0xE259,
        "0xE259",
        IconFontFamily::Material,
        "Material",
        "MatIcon::VerticalAlignCenter",
        "Vertical Align Center"
    },
    {
        0xE25A,
        "0xE25A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::VerticalAlignTop",
        "Vertical Align Top"
    },
    {
        0xE62D,
        "0xE62D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Vibration",
        "Vibration"
    },
    {
        0xE070,
        "0xE070",
        IconFontFamily::Material,
        "Material",
        "MatIcon::VideoCall",
        "Video Call"
    },
    {
        0xE071,
        "0xE071",
        IconFontFamily::Material,
        "Material",
        "MatIcon::VideoLabel",
        "Video Label"
    },
    {
        0xE04A,
        "0xE04A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::VideoLibrary",
        "Video Library"
    },
    {
        0xE04B,
        "0xE04B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Videocam",
        "Videocam"
    },
    {
        0xE04C,
        "0xE04C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::VideocamOff",
        "Videocam Off"
    },
    {
        0xE338,
        "0xE338",
        IconFontFamily::Material,
        "Material",
        "MatIcon::VideogameAsset",
        "Videogame Asset"
    },
    {
        0xE8E9,
        "0xE8E9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ViewAgenda",
        "View Agenda"
    },
    {
        0xE8EA,
        "0xE8EA",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ViewArray",
        "View Array"
    },
    {
        0xE8EB,
        "0xE8EB",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ViewCarousel",
        "View Carousel"
    },
    {
        0xE8EC,
        "0xE8EC",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ViewColumn",
        "View Column"
    },
    {
        0xE42A,
        "0xE42A",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ViewComfy",
        "View Comfy"
    },
    {
        0xE42B,
        "0xE42B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ViewCompact",
        "View Compact"
    },
    {
        0xE8ED,
        "0xE8ED",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ViewDay",
        "View Day"
    },
    {
        0xE8EE,
        "0xE8EE",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ViewHeadline",
        "View Headline"
    },
    {
        0xE8EF,
        "0xE8EF",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ViewList",
        "View List"
    },
    {
        0xE8F0,
        "0xE8F0",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ViewModule",
        "View Module"
    },
    {
        0xE8F1,
        "0xE8F1",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ViewQuilt",
        "View Quilt"
    },
    {
        0xE8F2,
        "0xE8F2",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ViewStream",
        "View Stream"
    },
    {
        0xE8F3,
        "0xE8F3",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ViewWeek",
        "View Week"
    },
    {
        0xE435,
        "0xE435",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Vignette",
        "Vignette"
    },
    {
        0xE8F4,
        "0xE8F4",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Visibility",
        "Visibility"
    },
    {
        0xE8F5,
        "0xE8F5",
        IconFontFamily::Material,
        "Material",
        "MatIcon::VisibilityOff",
        "Visibility Off"
    },
    {
        0xE62E,
        "0xE62E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::VoiceChat",
        "Voice Chat"
    },
    {
        0xE0D9,
        "0xE0D9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Voicemail",
        "Voicemail"
    },
    {
        0xE04D,
        "0xE04D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::VolumeDown",
        "Volume Down"
    },
    {
        0xE04E,
        "0xE04E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::VolumeMute",
        "Volume Mute"
    },
    {
        0xE04F,
        "0xE04F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::VolumeOff",
        "Volume Off"
    },
    {
        0xE050,
        "0xE050",
        IconFontFamily::Material,
        "Material",
        "MatIcon::VolumeUp",
        "Volume Up"
    },
    {
        0xE0DA,
        "0xE0DA",
        IconFontFamily::Material,
        "Material",
        "MatIcon::VpnKey",
        "Vpn Key"
    },
    {
        0xE62F,
        "0xE62F",
        IconFontFamily::Material,
        "Material",
        "MatIcon::VpnLock",
        "Vpn Lock"
    },
    {
        0xE1BC,
        "0xE1BC",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Wallpaper",
        "Wallpaper"
    },
    {
        0xE002,
        "0xE002",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Warning",
        "Warning"
    },
    {
        0xE334,
        "0xE334",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Watch",
        "Watch"
    },
    {
        0xE924,
        "0xE924",
        IconFontFamily::Material,
        "Material",
        "MatIcon::WatchLater",
        "Watch Later"
    },
    {
        0xE42C,
        "0xE42C",
        IconFontFamily::Material,
        "Material",
        "MatIcon::WbAuto",
        "Wb Auto"
    },
    {
        0xE42D,
        "0xE42D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::WbCloudy",
        "Wb Cloudy"
    },
    {
        0xE42E,
        "0xE42E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::WbIncandescent",
        "Wb Incandescent"
    },
    {
        0xE436,
        "0xE436",
        IconFontFamily::Material,
        "Material",
        "MatIcon::WbIridescent",
        "Wb Iridescent"
    },
    {
        0xE430,
        "0xE430",
        IconFontFamily::Material,
        "Material",
        "MatIcon::WbSunny",
        "Wb Sunny"
    },
    {
        0xE63D,
        "0xE63D",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Wc",
        "Wc"
    },
    {
        0xE051,
        "0xE051",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Web",
        "Web"
    },
    {
        0xE069,
        "0xE069",
        IconFontFamily::Material,
        "Material",
        "MatIcon::WebAsset",
        "Web Asset"
    },
    {
        0xE16B,
        "0xE16B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Weekend",
        "Weekend"
    },
    {
        0xE80E,
        "0xE80E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Whatshot",
        "Whatshot"
    },
    {
        0xE1BD,
        "0xE1BD",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Widgets",
        "Widgets"
    },
    {
        0xE63E,
        "0xE63E",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Wifi",
        "Wifi"
    },
    {
        0xE1E1,
        "0xE1E1",
        IconFontFamily::Material,
        "Material",
        "MatIcon::WifiLock",
        "Wifi Lock"
    },
    {
        0xE1E2,
        "0xE1E2",
        IconFontFamily::Material,
        "Material",
        "MatIcon::WifiTethering",
        "Wifi Tethering"
    },
    {
        0xE8F9,
        "0xE8F9",
        IconFontFamily::Material,
        "Material",
        "MatIcon::Work",
        "Work"
    },
    {
        0xE25B,
        "0xE25B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::WrapText",
        "Wrap Text"
    },
    {
        0xE8FA,
        "0xE8FA",
        IconFontFamily::Material,
        "Material",
        "MatIcon::YoutubeSearchedFor",
        "Youtube Searched For"
    },
    {
        0xE8FF,
        "0xE8FF",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ZoomIn",
        "Zoom In"
    },
    {
        0xE900,
        "0xE900",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ZoomOut",
        "Zoom Out"
    },
    {
        0xE56B,
        "0xE56B",
        IconFontFamily::Material,
        "Material",
        "MatIcon::ZoomOutMap",
        "Zoom Out Map"
    },
    {
        0xF26E,
        "0xF26E",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::_500px",
        "500 px"
    },
    {
        0xF368,
        "0xF368",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::AccessibleIcon",
        "Accessible Icon"
    },
    {
        0xF369,
        "0xF369",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Accusoft",
        "Accusoft"
    },
    {
        0xF170,
        "0xF170",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Adn",
        "Adn"
    },
    {
        0xF36A,
        "0xF36A",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Adversal",
        "Adversal"
    },
    {
        0xF36B,
        "0xF36B",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Affiliatetheme",
        "Affiliatetheme"
    },
    {
        0xF36C,
        "0xF36C",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Algolia",
        "Algolia"
    },
    {
        0xF270,
        "0xF270",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Amazon",
        "Amazon"
    },
    {
        0xF42C,
        "0xF42C",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::AmazonPay",
        "Amazon Pay"
    },
    {
        0xF36D,
        "0xF36D",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Amilia",
        "Amilia"
    },
    {
        0xF17B,
        "0xF17B",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Android",
        "Android"
    },
    {
        0xF209,
        "0xF209",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Angellist",
        "Angellist"
    },
    {
        0xF36E,
        "0xF36E",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Angrycreative",
        "Angrycreative"
    },
    {
        0xF420,
        "0xF420",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Angular",
        "Angular"
    },
    {
        0xF36F,
        "0xF36F",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::AppStore",
        "App Store"
    },
    {
        0xF370,
        "0xF370",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::AppStoreIos",
        "App Store Ios"
    },
    {
        0xF371,
        "0xF371",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Apper",
        "Apper"
    },
    {
        0xF179,
        "0xF179",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Apple",
        "Apple"
    },
    {
        0xF415,
        "0xF415",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::ApplePay",
        "Apple Pay"
    },
    {
        0xF372,
        "0xF372",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Asymmetrik",
        "Asymmetrik"
    },
    {
        0xF373,
        "0xF373",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Audible",
        "Audible"
    },
    {
        0xF41C,
        "0xF41C",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Autoprefixer",
        "Autoprefixer"
    },
    {
        0xF374,
        "0xF374",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Avianex",
        "Avianex"
    },
    {
        0xF421,
        "0xF421",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Aviato",
        "Aviato"
    },
    {
        0xF375,
        "0xF375",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Aws",
        "Aws"
    },
    {
        0xF2D5,
        "0xF2D5",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Bandcamp",
        "Bandcamp"
    },
    {
        0xF1B4,
        "0xF1B4",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Behance",
        "Behance"
    },
    {
        0xF1B5,
        "0xF1B5",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::BehanceSquare",
        "Behance Square"
    },
    {
        0xF378,
        "0xF378",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Bimobject",
        "Bimobject"
    },
    {
        0xF171,
        "0xF171",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Bitbucket",
        "Bitbucket"
    },
    {
        0xF379,
        "0xF379",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Bitcoin",
        "Bitcoin"
    },
    {
        0xF37A,
        "0xF37A",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Bity",
        "Bity"
    },
    {
        0xF27E,
        "0xF27E",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::BlackTie",
        "Black Tie"
    },
    {
        0xF37B,
        "0xF37B",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Blackberry",
        "Blackberry"
    },
    {
        0xF37C,
        "0xF37C",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Blogger",
        "Blogger"
    },
    {
        0xF37D,
        "0xF37D",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::BloggerB",
        "Blogger B"
    },
    {
        0xF293,
        "0xF293",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Bluetooth",
        "Bluetooth"
    },
    {
        0xF294,
        "0xF294",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::BluetoothB",
        "Bluetooth B"
    },
    {
        0xF15A,
        "0xF15A",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Btc",
        "Btc"
    },
    {
        0xF37F,
        "0xF37F",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Buromobelexperte",
        "Buromobelexperte"
    },
    {
        0xF20D,
        "0xF20D",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Buysellads",
        "Buysellads"
    },
    {
        0xF42D,
        "0xF42D",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CcAmazonPay",
        "Cc Amazon Pay"
    },
    {
        0xF1F3,
        "0xF1F3",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CcAmex",
        "Cc Amex"
    },
    {
        0xF416,
        "0xF416",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CcApplePay",
        "Cc Apple Pay"
    },
    {
        0xF24C,
        "0xF24C",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CcDinersClub",
        "Cc Diners Club"
    },
    {
        0xF1F2,
        "0xF1F2",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CcDiscover",
        "Cc Discover"
    },
    {
        0xF24B,
        "0xF24B",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CcJcb",
        "Cc Jcb"
    },
    {
        0xF1F1,
        "0xF1F1",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CcMastercard",
        "Cc Mastercard"
    },
    {
        0xF1F4,
        "0xF1F4",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CcPaypal",
        "Cc Paypal"
    },
    {
        0xF1F5,
        "0xF1F5",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CcStripe",
        "Cc Stripe"
    },
    {
        0xF1F0,
        "0xF1F0",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CcVisa",
        "Cc Visa"
    },
    {
        0xF380,
        "0xF380",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Centercode",
        "Centercode"
    },
    {
        0xF268,
        "0xF268",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Chrome",
        "Chrome"
    },
    {
        0xF383,
        "0xF383",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Cloudscale",
        "Cloudscale"
    },
    {
        0xF384,
        "0xF384",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Cloudsmith",
        "Cloudsmith"
    },
    {
        0xF385,
        "0xF385",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Cloudversify",
        "Cloudversify"
    },
    {
        0xF1CB,
        "0xF1CB",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Codepen",
        "Codepen"
    },
    {
        0xF284,
        "0xF284",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Codiepie",
        "Codiepie"
    },
    {
        0xF20E,
        "0xF20E",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Connectdevelop",
        "Connectdevelop"
    },
    {
        0xF26D,
        "0xF26D",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Contao",
        "Contao"
    },
    {
        0xF388,
        "0xF388",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Cpanel",
        "Cpanel"
    },
    {
        0xF25E,
        "0xF25E",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CreativeCommons",
        "Creative Commons"
    },
    {
        0xF4E7,
        "0xF4E7",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CreativeCommonsBy",
        "Creative Commons By"
    },
    {
        0xF4E8,
        "0xF4E8",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CreativeCommonsNc",
        "Creative Commons Nc"
    },
    {
        0xF4E9,
        "0xF4E9",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CreativeCommonsNcEu",
        "Creative Commons Nc Eu"
    },
    {
        0xF4EA,
        "0xF4EA",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CreativeCommonsNcJp",
        "Creative Commons Nc Jp"
    },
    {
        0xF4EB,
        "0xF4EB",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CreativeCommonsNd",
        "Creative Commons Nd"
    },
    {
        0xF4EC,
        "0xF4EC",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CreativeCommonsPd",
        "Creative Commons Pd"
    },
    {
        0xF4ED,
        "0xF4ED",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CreativeCommonsPdAlt",
        "Creative Commons Pd Alt"
    },
    {
        0xF4EE,
        "0xF4EE",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CreativeCommonsRemix",
        "Creative Commons Remix"
    },
    {
        0xF4EF,
        "0xF4EF",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CreativeCommonsSa",
        "Creative Commons Sa"
    },
    {
        0xF4F0,
        "0xF4F0",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CreativeCommonsSampling",
        "Creative Commons Sampling"
    },
    {
        0xF4F1,
        "0xF4F1",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CreativeCommonsSamplingPlus",
        "Creative Commons Sampling Plus"
    },
    {
        0xF4F2,
        "0xF4F2",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::CreativeCommonsShare",
        "Creative Commons Share"
    },
    {
        0xF13C,
        "0xF13C",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Css3",
        "Css 3"
    },
    {
        0xF38B,
        "0xF38B",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Css3Alt",
        "Css 3 Alt"
    },
    {
        0xF38C,
        "0xF38C",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Cuttlefish",
        "Cuttlefish"
    },
    {
        0xF38D,
        "0xF38D",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::DAndD",
        "D And D"
    },
    {
        0xF210,
        "0xF210",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Dashcube",
        "Dashcube"
    },
    {
        0xF1A5,
        "0xF1A5",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Delicious",
        "Delicious"
    },
    {
        0xF38E,
        "0xF38E",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Deploydog",
        "Deploydog"
    },
    {
        0xF38F,
        "0xF38F",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Deskpro",
        "Deskpro"
    },
    {
        0xF1BD,
        "0xF1BD",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Deviantart",
        "Deviantart"
    },
    {
        0xF1A6,
        "0xF1A6",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Digg",
        "Digg"
    },
    {
        0xF391,
        "0xF391",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::DigitalOcean",
        "Digital Ocean"
    },
    {
        0xF392,
        "0xF392",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Discord",
        "Discord"
    },
    {
        0xF393,
        "0xF393",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Discourse",
        "Discourse"
    },
    {
        0xF394,
        "0xF394",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Dochub",
        "Dochub"
    },
    {
        0xF395,
        "0xF395",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Docker",
        "Docker"
    },
    {
        0xF396,
        "0xF396",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Draft2digital",
        "Draft 2 digital"
    },
    {
        0xF17D,
        "0xF17D",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Dribbble",
        "Dribbble"
    },
    {
        0xF397,
        "0xF397",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::DribbbleSquare",
        "Dribbble Square"
    },
    {
        0xF16B,
        "0xF16B",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Dropbox",
        "Dropbox"
    },
    {
        0xF1A9,
        "0xF1A9",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Drupal",
        "Drupal"
    },
    {
        0xF399,
        "0xF399",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Dyalog",
        "Dyalog"
    },
    {
        0xF39A,
        "0xF39A",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Earlybirds",
        "Earlybirds"
    },
    {
        0xF4F4,
        "0xF4F4",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Ebay",
        "Ebay"
    },
    {
        0xF282,
        "0xF282",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Edge",
        "Edge"
    },
    {
        0xF430,
        "0xF430",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Elementor",
        "Elementor"
    },
    {
        0xF423,
        "0xF423",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Ember",
        "Ember"
    },
    {
        0xF1D1,
        "0xF1D1",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Empire",
        "Empire"
    },
    {
        0xF299,
        "0xF299",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Envira",
        "Envira"
    },
    {
        0xF39D,
        "0xF39D",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Erlang",
        "Erlang"
    },
    {
        0xF42E,
        "0xF42E",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Ethereum",
        "Ethereum"
    },
    {
        0xF2D7,
        "0xF2D7",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Etsy",
        "Etsy"
    },
    {
        0xF23E,
        "0xF23E",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Expeditedssl",
        "Expeditedssl"
    },
    {
        0xF09A,
        "0xF09A",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Facebook",
        "Facebook"
    },
    {
        0xF39E,
        "0xF39E",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::FacebookF",
        "Facebook F"
    },
    {
        0xF39F,
        "0xF39F",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::FacebookMessenger",
        "Facebook Messenger"
    },
    {
        0xF082,
        "0xF082",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::FacebookSquare",
        "Facebook Square"
    },
    {
        0xF269,
        "0xF269",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Firefox",
        "Firefox"
    },
    {
        0xF2B0,
        "0xF2B0",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::FirstOrder",
        "First Order"
    },
    {
        0xF50A,
        "0xF50A",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::FirstOrderAlt",
        "First Order Alt"
    },
    {
        0xF3A1,
        "0xF3A1",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Firstdraft",
        "Firstdraft"
    },
    {
        0xF16E,
        "0xF16E",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Flickr",
        "Flickr"
    },
    {
        0xF44D,
        "0xF44D",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Flipboard",
        "Flipboard"
    },
    {
        0xF417,
        "0xF417",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Fly",
        "Fly"
    },
    {
        0xF2B4,
        "0xF2B4",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::FontAwesome",
        "Font Awesome"
    },
    {
        0xF35C,
        "0xF35C",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::FontAwesomeAlt",
        "Font Awesome Alt"
    },
    {
        0xF425,
        "0xF425",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::FontAwesomeFlag",
        "Font Awesome Flag"
    },
    {
        0xF4E6,
        "0xF4E6",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::FontAwesomeLogoFull",
        "Font Awesome Logo Full"
    },
    {
        0xF280,
        "0xF280",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Fonticons",
        "Fonticons"
    },
    {
        0xF3A2,
        "0xF3A2",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::FonticonsFi",
        "Fonticons Fi"
    },
    {
        0xF286,
        "0xF286",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::FortAwesome",
        "Fort Awesome"
    },
    {
        0xF3A3,
        "0xF3A3",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::FortAwesomeAlt",
        "Fort Awesome Alt"
    },
    {
        0xF211,
        "0xF211",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Forumbee",
        "Forumbee"
    },
    {
        0xF180,
        "0xF180",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Foursquare",
        "Foursquare"
    },
    {
        0xF2C5,
        "0xF2C5",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::FreeCodeCamp",
        "Free Code Camp"
    },
    {
        0xF3A4,
        "0xF3A4",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Freebsd",
        "Freebsd"
    },
    {
        0xF50B,
        "0xF50B",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Fulcrum",
        "Fulcrum"
    },
    {
        0xF50C,
        "0xF50C",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::GalacticRepublic",
        "Galactic Republic"
    },
    {
        0xF50D,
        "0xF50D",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::GalacticSenate",
        "Galactic Senate"
    },
    {
        0xF265,
        "0xF265",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::GetPocket",
        "Get Pocket"
    },
    {
        0xF260,
        "0xF260",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Gg",
        "Gg"
    },
    {
        0xF261,
        "0xF261",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::GgCircle",
        "Gg Circle"
    },
    {
        0xF1D3,
        "0xF1D3",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Git",
        "Git"
    },
    {
        0xF1D2,
        "0xF1D2",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::GitSquare",
        "Git Square"
    },
    {
        0xF09B,
        "0xF09B",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Github",
        "Github"
    },
    {
        0xF113,
        "0xF113",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::GithubAlt",
        "Github Alt"
    },
    {
        0xF092,
        "0xF092",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::GithubSquare",
        "Github Square"
    },
    {
        0xF3A6,
        "0xF3A6",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Gitkraken",
        "Gitkraken"
    },
    {
        0xF296,
        "0xF296",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Gitlab",
        "Gitlab"
    },
    {
        0xF426,
        "0xF426",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Gitter",
        "Gitter"
    },
    {
        0xF2A5,
        "0xF2A5",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Glide",
        "Glide"
    },
    {
        0xF2A6,
        "0xF2A6",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::GlideG",
        "Glide G"
    },
    {
        0xF3A7,
        "0xF3A7",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Gofore",
        "Gofore"
    },
    {
        0xF3A8,
        "0xF3A8",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Goodreads",
        "Goodreads"
    },
    {
        0xF3A9,
        "0xF3A9",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::GoodreadsG",
        "Goodreads G"
    },
    {
        0xF1A0,
        "0xF1A0",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Google",
        "Google"
    },
    {
        0xF3AA,
        "0xF3AA",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::GoogleDrive",
        "Google Drive"
    },
    {
        0xF3AB,
        "0xF3AB",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::GooglePlay",
        "Google Play"
    },
    {
        0xF2B3,
        "0xF2B3",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::GooglePlus",
        "Google Plus"
    },
    {
        0xF0D5,
        "0xF0D5",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::GooglePlusG",
        "Google Plus G"
    },
    {
        0xF0D4,
        "0xF0D4",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::GooglePlusSquare",
        "Google Plus Square"
    },
    {
        0xF1EE,
        "0xF1EE",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::GoogleWallet",
        "Google Wallet"
    },
    {
        0xF184,
        "0xF184",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Gratipay",
        "Gratipay"
    },
    {
        0xF2D6,
        "0xF2D6",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Grav",
        "Grav"
    },
    {
        0xF3AC,
        "0xF3AC",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Gripfire",
        "Gripfire"
    },
    {
        0xF3AD,
        "0xF3AD",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Grunt",
        "Grunt"
    },
    {
        0xF3AE,
        "0xF3AE",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Gulp",
        "Gulp"
    },
    {
        0xF1D4,
        "0xF1D4",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::HackerNews",
        "Hacker News"
    },
    {
        0xF3AF,
        "0xF3AF",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::HackerNewsSquare",
        "Hacker News Square"
    },
    {
        0xF452,
        "0xF452",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Hips",
        "Hips"
    },
    {
        0xF3B0,
        "0xF3B0",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::HireAHelper",
        "Hire A Helper"
    },
    {
        0xF427,
        "0xF427",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Hooli",
        "Hooli"
    },
    {
        0xF592,
        "0xF592",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Hornbill",
        "Hornbill"
    },
    {
        0xF3B1,
        "0xF3B1",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Hotjar",
        "Hotjar"
    },
    {
        0xF27C,
        "0xF27C",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Houzz",
        "Houzz"
    },
    {
        0xF13B,
        "0xF13B",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Html5",
        "Html 5"
    },
    {
        0xF3B2,
        "0xF3B2",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Hubspot",
        "Hubspot"
    },
    {
        0xF2D8,
        "0xF2D8",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Imdb",
        "Imdb"
    },
    {
        0xF16D,
        "0xF16D",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Instagram",
        "Instagram"
    },
    {
        0xF26B,
        "0xF26B",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::InternetExplorer",
        "Internet Explorer"
    },
    {
        0xF208,
        "0xF208",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Ioxhost",
        "Ioxhost"
    },
    {
        0xF3B4,
        "0xF3B4",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Itunes",
        "Itunes"
    },
    {
        0xF3B5,
        "0xF3B5",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::ItunesNote",
        "Itunes Note"
    },
    {
        0xF4E4,
        "0xF4E4",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Java",
        "Java"
    },
    {
        0xF50E,
        "0xF50E",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::JediOrder",
        "Jedi Order"
    },
    {
        0xF3B6,
        "0xF3B6",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Jenkins",
        "Jenkins"
    },
    {
        0xF3B7,
        "0xF3B7",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Joget",
        "Joget"
    },
    {
        0xF1AA,
        "0xF1AA",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Joomla",
        "Joomla"
    },
    {
        0xF3B8,
        "0xF3B8",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Js",
        "Js"
    },
    {
        0xF3B9,
        "0xF3B9",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::JsSquare",
        "Js Square"
    },
    {
        0xF1CC,
        "0xF1CC",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Jsfiddle",
        "Jsfiddle"
    },
    {
        0xF4F5,
        "0xF4F5",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Keybase",
        "Keybase"
    },
    {
        0xF3BA,
        "0xF3BA",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Keycdn",
        "Keycdn"
    },
    {
        0xF3BB,
        "0xF3BB",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Kickstarter",
        "Kickstarter"
    },
    {
        0xF3BC,
        "0xF3BC",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::KickstarterK",
        "Kickstarter K"
    },
    {
        0xF42F,
        "0xF42F",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Korvue",
        "Korvue"
    },
    {
        0xF3BD,
        "0xF3BD",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Laravel",
        "Laravel"
    },
    {
        0xF202,
        "0xF202",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Lastfm",
        "Lastfm"
    },
    {
        0xF203,
        "0xF203",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::LastfmSquare",
        "Lastfm Square"
    },
    {
        0xF212,
        "0xF212",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Leanpub",
        "Leanpub"
    },
    {
        0xF41D,
        "0xF41D",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Less",
        "Less"
    },
    {
        0xF3C0,
        "0xF3C0",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Line",
        "Line"
    },
    {
        0xF08C,
        "0xF08C",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Linkedin",
        "Linkedin"
    },
    {
        0xF0E1,
        "0xF0E1",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::LinkedinIn",
        "Linkedin In"
    },
    {
        0xF2B8,
        "0xF2B8",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Linode",
        "Linode"
    },
    {
        0xF17C,
        "0xF17C",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Linux",
        "Linux"
    },
    {
        0xF3C3,
        "0xF3C3",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Lyft",
        "Lyft"
    },
    {
        0xF3C4,
        "0xF3C4",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Magento",
        "Magento"
    },
    {
        0xF59E,
        "0xF59E",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Mailchimp",
        "Mailchimp"
    },
    {
        0xF50F,
        "0xF50F",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Mandalorian",
        "Mandalorian"
    },
    {
        0xF4F6,
        "0xF4F6",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Mastodon",
        "Mastodon"
    },
    {
        0xF136,
        "0xF136",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Maxcdn",
        "Maxcdn"
    },
    {
        0xF3C6,
        "0xF3C6",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Medapps",
        "Medapps"
    },
    {
        0xF23A,
        "0xF23A",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Medium",
        "Medium"
    },
    {
        0xF3C7,
        "0xF3C7",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::MediumM",
        "Medium M"
    },
    {
        0xF3C8,
        "0xF3C8",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Medrt",
        "Medrt"
    },
    {
        0xF2E0,
        "0xF2E0",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Meetup",
        "Meetup"
    },
    {
        0xF5A3,
        "0xF5A3",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Megaport",
        "Megaport"
    },
    {
        0xF3CA,
        "0xF3CA",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Microsoft",
        "Microsoft"
    },
    {
        0xF3CB,
        "0xF3CB",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Mix",
        "Mix"
    },
    {
        0xF289,
        "0xF289",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Mixcloud",
        "Mixcloud"
    },
    {
        0xF3CC,
        "0xF3CC",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Mizuni",
        "Mizuni"
    },
    {
        0xF285,
        "0xF285",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Modx",
        "Modx"
    },
    {
        0xF3D0,
        "0xF3D0",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Monero",
        "Monero"
    },
    {
        0xF3D2,
        "0xF3D2",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Napster",
        "Napster"
    },
    {
        0xF5A8,
        "0xF5A8",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Nimblr",
        "Nimblr"
    },
    {
        0xF418,
        "0xF418",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::NintendoSwitch",
        "Nintendo Switch"
    },
    {
        0xF419,
        "0xF419",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Node",
        "Node"
    },
    {
        0xF3D3,
        "0xF3D3",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::NodeJs",
        "Node Js"
    },
    {
        0xF3D4,
        "0xF3D4",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Npm",
        "Npm"
    },
    {
        0xF3D5,
        "0xF3D5",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Ns8",
        "Ns 8"
    },
    {
        0xF3D6,
        "0xF3D6",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Nutritionix",
        "Nutritionix"
    },
    {
        0xF263,
        "0xF263",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Odnoklassniki",
        "Odnoklassniki"
    },
    {
        0xF264,
        "0xF264",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::OdnoklassnikiSquare",
        "Odnoklassniki Square"
    },
    {
        0xF510,
        "0xF510",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::OldRepublic",
        "Old Republic"
    },
    {
        0xF23D,
        "0xF23D",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Opencart",
        "Opencart"
    },
    {
        0xF19B,
        "0xF19B",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Openid",
        "Openid"
    },
    {
        0xF26A,
        "0xF26A",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Opera",
        "Opera"
    },
    {
        0xF23C,
        "0xF23C",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::OptinMonster",
        "Optin Monster"
    },
    {
        0xF41A,
        "0xF41A",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Osi",
        "Osi"
    },
    {
        0xF3D7,
        "0xF3D7",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Page4",
        "Page 4"
    },
    {
        0xF18C,
        "0xF18C",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Pagelines",
        "Pagelines"
    },
    {
        0xF3D8,
        "0xF3D8",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Palfed",
        "Palfed"
    },
    {
        0xF3D9,
        "0xF3D9",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Patreon",
        "Patreon"
    },
    {
        0xF1ED,
        "0xF1ED",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Paypal",
        "Paypal"
    },
    {
        0xF3DA,
        "0xF3DA",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Periscope",
        "Periscope"
    },
    {
        0xF3DB,
        "0xF3DB",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Phabricator",
        "Phabricator"
    },
    {
        0xF3DC,
        "0xF3DC",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::PhoenixFramework",
        "Phoenix Framework"
    },
    {
        0xF511,
        "0xF511",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::PhoenixSquadron",
        "Phoenix Squadron"
    },
    {
        0xF457,
        "0xF457",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Php",
        "Php"
    },
    {
        0xF2AE,
        "0xF2AE",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::PiedPiper",
        "Pied Piper"
    },
    {
        0xF1A8,
        "0xF1A8",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::PiedPiperAlt",
        "Pied Piper Alt"
    },
    {
        0xF4E5,
        "0xF4E5",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::PiedPiperHat",
        "Pied Piper Hat"
    },
    {
        0xF1A7,
        "0xF1A7",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::PiedPiperPp",
        "Pied Piper Pp"
    },
    {
        0xF0D2,
        "0xF0D2",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Pinterest",
        "Pinterest"
    },
    {
        0xF231,
        "0xF231",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::PinterestP",
        "Pinterest P"
    },
    {
        0xF0D3,
        "0xF0D3",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::PinterestSquare",
        "Pinterest Square"
    },
    {
        0xF3DF,
        "0xF3DF",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Playstation",
        "Playstation"
    },
    {
        0xF288,
        "0xF288",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::ProductHunt",
        "Product Hunt"
    },
    {
        0xF3E1,
        "0xF3E1",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Pushed",
        "Pushed"
    },
    {
        0xF3E2,
        "0xF3E2",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Python",
        "Python"
    },
    {
        0xF1D6,
        "0xF1D6",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Qq",
        "Qq"
    },
    {
        0xF459,
        "0xF459",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Quinscape",
        "Quinscape"
    },
    {
        0xF2C4,
        "0xF2C4",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Quora",
        "Quora"
    },
    {
        0xF4F7,
        "0xF4F7",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::RProject",
        "R Project"
    },
    {
        0xF2D9,
        "0xF2D9",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Ravelry",
        "Ravelry"
    },
    {
        0xF41B,
        "0xF41B",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::React",
        "React"
    },
    {
        0xF4D5,
        "0xF4D5",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Readme",
        "Readme"
    },
    {
        0xF1D0,
        "0xF1D0",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Rebel",
        "Rebel"
    },
    {
        0xF3E3,
        "0xF3E3",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::RedRiver",
        "Red River"
    },
    {
        0xF1A1,
        "0xF1A1",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Reddit",
        "Reddit"
    },
    {
        0xF281,
        "0xF281",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::RedditAlien",
        "Reddit Alien"
    },
    {
        0xF1A2,
        "0xF1A2",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::RedditSquare",
        "Reddit Square"
    },
    {
        0xF3E4,
        "0xF3E4",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Rendact",
        "Rendact"
    },
    {
        0xF18B,
        "0xF18B",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Renren",
        "Renren"
    },
    {
        0xF3E6,
        "0xF3E6",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Replyd",
        "Replyd"
    },
    {
        0xF4F8,
        "0xF4F8",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Researchgate",
        "Researchgate"
    },
    {
        0xF3E7,
        "0xF3E7",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Resolving",
        "Resolving"
    },
    {
        0xF3E8,
        "0xF3E8",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Rocketchat",
        "Rocketchat"
    },
    {
        0xF3E9,
        "0xF3E9",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Rockrms",
        "Rockrms"
    },
    {
        0xF267,
        "0xF267",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Safari",
        "Safari"
    },
    {
        0xF41E,
        "0xF41E",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Sass",
        "Sass"
    },
    {
        0xF3EA,
        "0xF3EA",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Schlix",
        "Schlix"
    },
    {
        0xF28A,
        "0xF28A",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Scribd",
        "Scribd"
    },
    {
        0xF3EB,
        "0xF3EB",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Searchengin",
        "Searchengin"
    },
    {
        0xF2DA,
        "0xF2DA",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Sellcast",
        "Sellcast"
    },
    {
        0xF213,
        "0xF213",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Sellsy",
        "Sellsy"
    },
    {
        0xF3EC,
        "0xF3EC",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Servicestack",
        "Servicestack"
    },
    {
        0xF214,
        "0xF214",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Shirtsinbulk",
        "Shirtsinbulk"
    },
    {
        0xF5B5,
        "0xF5B5",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Shopware",
        "Shopware"
    },
    {
        0xF215,
        "0xF215",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Simplybuilt",
        "Simplybuilt"
    },
    {
        0xF3EE,
        "0xF3EE",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Sistrix",
        "Sistrix"
    },
    {
        0xF512,
        "0xF512",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Sith",
        "Sith"
    },
    {
        0xF216,
        "0xF216",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Skyatlas",
        "Skyatlas"
    },
    {
        0xF17E,
        "0xF17E",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Skype",
        "Skype"
    },
    {
        0xF198,
        "0xF198",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Slack",
        "Slack"
    },
    {
        0xF3EF,
        "0xF3EF",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::SlackHash",
        "Slack Hash"
    },
    {
        0xF1E7,
        "0xF1E7",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Slideshare",
        "Slideshare"
    },
    {
        0xF2AB,
        "0xF2AB",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Snapchat",
        "Snapchat"
    },
    {
        0xF2AC,
        "0xF2AC",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::SnapchatGhost",
        "Snapchat Ghost"
    },
    {
        0xF2AD,
        "0xF2AD",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::SnapchatSquare",
        "Snapchat Square"
    },
    {
        0xF1BE,
        "0xF1BE",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Soundcloud",
        "Soundcloud"
    },
    {
        0xF3F3,
        "0xF3F3",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Speakap",
        "Speakap"
    },
    {
        0xF1BC,
        "0xF1BC",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Spotify",
        "Spotify"
    },
    {
        0xF5BE,
        "0xF5BE",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Squarespace",
        "Squarespace"
    },
    {
        0xF18D,
        "0xF18D",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::StackExchange",
        "Stack Exchange"
    },
    {
        0xF16C,
        "0xF16C",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::StackOverflow",
        "Stack Overflow"
    },
    {
        0xF3F5,
        "0xF3F5",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Staylinked",
        "Staylinked"
    },
    {
        0xF1B6,
        "0xF1B6",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Steam",
        "Steam"
    },
    {
        0xF1B7,
        "0xF1B7",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::SteamSquare",
        "Steam Square"
    },
    {
        0xF3F6,
        "0xF3F6",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::SteamSymbol",
        "Steam Symbol"
    },
    {
        0xF3F7,
        "0xF3F7",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::StickerMule",
        "Sticker Mule"
    },
    {
        0xF428,
        "0xF428",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Strava",
        "Strava"
    },
    {
        0xF429,
        "0xF429",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Stripe",
        "Stripe"
    },
    {
        0xF42A,
        "0xF42A",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::StripeS",
        "Stripe S"
    },
    {
        0xF3F8,
        "0xF3F8",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Studiovinari",
        "Studiovinari"
    },
    {
        0xF1A4,
        "0xF1A4",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Stumbleupon",
        "Stumbleupon"
    },
    {
        0xF1A3,
        "0xF1A3",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::StumbleuponCircle",
        "Stumbleupon Circle"
    },
    {
        0xF2DD,
        "0xF2DD",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Superpowers",
        "Superpowers"
    },
    {
        0xF3F9,
        "0xF3F9",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Supple",
        "Supple"
    },
    {
        0xF4F9,
        "0xF4F9",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Teamspeak",
        "Teamspeak"
    },
    {
        0xF2C6,
        "0xF2C6",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Telegram",
        "Telegram"
    },
    {
        0xF3FE,
        "0xF3FE",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::TelegramPlane",
        "Telegram Plane"
    },
    {
        0xF1D5,
        "0xF1D5",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::TencentWeibo",
        "Tencent Weibo"
    },
    {
        0xF5C6,
        "0xF5C6",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Themeco",
        "Themeco"
    },
    {
        0xF2B2,
        "0xF2B2",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Themeisle",
        "Themeisle"
    },
    {
        0xF513,
        "0xF513",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::TradeFederation",
        "Trade Federation"
    },
    {
        0xF181,
        "0xF181",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Trello",
        "Trello"
    },
    {
        0xF262,
        "0xF262",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Tripadvisor",
        "Tripadvisor"
    },
    {
        0xF173,
        "0xF173",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Tumblr",
        "Tumblr"
    },
    {
        0xF174,
        "0xF174",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::TumblrSquare",
        "Tumblr Square"
    },
    {
        0xF1E8,
        "0xF1E8",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Twitch",
        "Twitch"
    },
    {
        0xF099,
        "0xF099",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Twitter",
        "Twitter"
    },
    {
        0xF081,
        "0xF081",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::TwitterSquare",
        "Twitter Square"
    },
    {
        0xF42B,
        "0xF42B",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Typo3",
        "Typo 3"
    },
    {
        0xF402,
        "0xF402",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Uber",
        "Uber"
    },
    {
        0xF403,
        "0xF403",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Uikit",
        "Uikit"
    },
    {
        0xF404,
        "0xF404",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Uniregistry",
        "Uniregistry"
    },
    {
        0xF405,
        "0xF405",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Untappd",
        "Untappd"
    },
    {
        0xF287,
        "0xF287",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Usb",
        "Usb"
    },
    {
        0xF407,
        "0xF407",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Ussunnah",
        "Ussunnah"
    },
    {
        0xF408,
        "0xF408",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Vaadin",
        "Vaadin"
    },
    {
        0xF237,
        "0xF237",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Viacoin",
        "Viacoin"
    },
    {
        0xF2A9,
        "0xF2A9",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Viadeo",
        "Viadeo"
    },
    {
        0xF2AA,
        "0xF2AA",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::ViadeoSquare",
        "Viadeo Square"
    },
    {
        0xF409,
        "0xF409",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Viber",
        "Viber"
    },
    {
        0xF40A,
        "0xF40A",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Vimeo",
        "Vimeo"
    },
    {
        0xF194,
        "0xF194",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::VimeoSquare",
        "Vimeo Square"
    },
    {
        0xF27D,
        "0xF27D",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::VimeoV",
        "Vimeo V"
    },
    {
        0xF1CA,
        "0xF1CA",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Vine",
        "Vine"
    },
    {
        0xF189,
        "0xF189",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Vk",
        "Vk"
    },
    {
        0xF40B,
        "0xF40B",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Vnv",
        "Vnv"
    },
    {
        0xF41F,
        "0xF41F",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Vuejs",
        "Vuejs"
    },
    {
        0xF5CC,
        "0xF5CC",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Weebly",
        "Weebly"
    },
    {
        0xF18A,
        "0xF18A",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Weibo",
        "Weibo"
    },
    {
        0xF1D7,
        "0xF1D7",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Weixin",
        "Weixin"
    },
    {
        0xF232,
        "0xF232",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Whatsapp",
        "Whatsapp"
    },
    {
        0xF40C,
        "0xF40C",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::WhatsappSquare",
        "Whatsapp Square"
    },
    {
        0xF40D,
        "0xF40D",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Whmcs",
        "Whmcs"
    },
    {
        0xF266,
        "0xF266",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::WikipediaW",
        "Wikipedia W"
    },
    {
        0xF17A,
        "0xF17A",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Windows",
        "Windows"
    },
    {
        0xF5CF,
        "0xF5CF",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Wix",
        "Wix"
    },
    {
        0xF514,
        "0xF514",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::WolfPackBattalion",
        "Wolf Pack Battalion"
    },
    {
        0xF19A,
        "0xF19A",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Wordpress",
        "Wordpress"
    },
    {
        0xF411,
        "0xF411",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::WordpressSimple",
        "Wordpress Simple"
    },
    {
        0xF297,
        "0xF297",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Wpbeginner",
        "Wpbeginner"
    },
    {
        0xF2DE,
        "0xF2DE",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Wpexplorer",
        "Wpexplorer"
    },
    {
        0xF298,
        "0xF298",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Wpforms",
        "Wpforms"
    },
    {
        0xF412,
        "0xF412",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Xbox",
        "Xbox"
    },
    {
        0xF168,
        "0xF168",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Xing",
        "Xing"
    },
    {
        0xF169,
        "0xF169",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::XingSquare",
        "Xing Square"
    },
    {
        0xF23B,
        "0xF23B",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::YCombinator",
        "Y Combinator"
    },
    {
        0xF19E,
        "0xF19E",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Yahoo",
        "Yahoo"
    },
    {
        0xF413,
        "0xF413",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Yandex",
        "Yandex"
    },
    {
        0xF414,
        "0xF414",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::YandexInternational",
        "Yandex International"
    },
    {
        0xF1E9,
        "0xF1E9",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Yelp",
        "Yelp"
    },
    {
        0xF2B1,
        "0xF2B1",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Yoast",
        "Yoast"
    },
    {
        0xF167,
        "0xF167",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::Youtube",
        "Youtube"
    },
    {
        0xF431,
        "0xF431",
        IconFontFamily::FontAwesomeBrands,
        "Font Awesome Brands",
        "FABrandIcon::YoutubeSquare",
        "Youtube Square"
    },
    {
        0xF2B9,
        "0xF2B9",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::AddressBook",
        "Address Book"
    },
    {
        0xF2BB,
        "0xF2BB",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::AddressCard",
        "Address Card"
    },
    {
        0xF042,
        "0xF042",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Adjust",
        "Adjust"
    },
    {
        0xF037,
        "0xF037",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::AlignCenter",
        "Align Center"
    },
    {
        0xF039,
        "0xF039",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::AlignJustify",
        "Align Justify"
    },
    {
        0xF036,
        "0xF036",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::AlignLeft",
        "Align Left"
    },
    {
        0xF038,
        "0xF038",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::AlignRight",
        "Align Right"
    },
    {
        0xF461,
        "0xF461",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Allergies",
        "Allergies"
    },
    {
        0xF0F9,
        "0xF0F9",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Ambulance",
        "Ambulance"
    },
    {
        0xF2A3,
        "0xF2A3",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::AmericanSignLanguageInterpreting",
        "American Sign Language Interpreting"
    },
    {
        0xF13D,
        "0xF13D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Anchor",
        "Anchor"
    },
    {
        0xF103,
        "0xF103",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::AngleDoubleDown",
        "Angle Double Down"
    },
    {
        0xF100,
        "0xF100",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::AngleDoubleLeft",
        "Angle Double Left"
    },
    {
        0xF101,
        "0xF101",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::AngleDoubleRight",
        "Angle Double Right"
    },
    {
        0xF102,
        "0xF102",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::AngleDoubleUp",
        "Angle Double Up"
    },
    {
        0xF107,
        "0xF107",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::AngleDown",
        "Angle Down"
    },
    {
        0xF104,
        "0xF104",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::AngleLeft",
        "Angle Left"
    },
    {
        0xF105,
        "0xF105",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::AngleRight",
        "Angle Right"
    },
    {
        0xF106,
        "0xF106",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::AngleUp",
        "Angle Up"
    },
    {
        0xF556,
        "0xF556",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Angry",
        "Angry"
    },
    {
        0xF187,
        "0xF187",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Archive",
        "Archive"
    },
    {
        0xF557,
        "0xF557",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Archway",
        "Archway"
    },
    {
        0xF358,
        "0xF358",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ArrowAltCircleDown",
        "Arrow Alt Circle Down"
    },
    {
        0xF359,
        "0xF359",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ArrowAltCircleLeft",
        "Arrow Alt Circle Left"
    },
    {
        0xF35A,
        "0xF35A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ArrowAltCircleRight",
        "Arrow Alt Circle Right"
    },
    {
        0xF35B,
        "0xF35B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ArrowAltCircleUp",
        "Arrow Alt Circle Up"
    },
    {
        0xF0AB,
        "0xF0AB",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ArrowCircleDown",
        "Arrow Circle Down"
    },
    {
        0xF0A8,
        "0xF0A8",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ArrowCircleLeft",
        "Arrow Circle Left"
    },
    {
        0xF0A9,
        "0xF0A9",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ArrowCircleRight",
        "Arrow Circle Right"
    },
    {
        0xF0AA,
        "0xF0AA",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ArrowCircleUp",
        "Arrow Circle Up"
    },
    {
        0xF063,
        "0xF063",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ArrowDown",
        "Arrow Down"
    },
    {
        0xF060,
        "0xF060",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ArrowLeft",
        "Arrow Left"
    },
    {
        0xF061,
        "0xF061",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ArrowRight",
        "Arrow Right"
    },
    {
        0xF062,
        "0xF062",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ArrowUp",
        "Arrow Up"
    },
    {
        0xF0B2,
        "0xF0B2",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ArrowsAlt",
        "Arrows Alt"
    },
    {
        0xF337,
        "0xF337",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ArrowsAltH",
        "Arrows Alt H"
    },
    {
        0xF338,
        "0xF338",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ArrowsAltV",
        "Arrows Alt V"
    },
    {
        0xF2A2,
        "0xF2A2",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::AssistiveListeningSystems",
        "Assistive Listening Systems"
    },
    {
        0xF069,
        "0xF069",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Asterisk",
        "Asterisk"
    },
    {
        0xF1FA,
        "0xF1FA",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::At",
        "At"
    },
    {
        0xF558,
        "0xF558",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Atlas",
        "Atlas"
    },
    {
        0xF29E,
        "0xF29E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::AudioDescription",
        "Audio Description"
    },
    {
        0xF559,
        "0xF559",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Award",
        "Award"
    },
    {
        0xF55A,
        "0xF55A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Backspace",
        "Backspace"
    },
    {
        0xF04A,
        "0xF04A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Backward",
        "Backward"
    },
    {
        0xF24E,
        "0xF24E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::BalanceScale",
        "Balance Scale"
    },
    {
        0xF05E,
        "0xF05E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Ban",
        "Ban"
    },
    {
        0xF462,
        "0xF462",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::BandAid",
        "Band Aid"
    },
    {
        0xF02A,
        "0xF02A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Barcode",
        "Barcode"
    },
    {
        0xF0C9,
        "0xF0C9",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Bars",
        "Bars"
    },
    {
        0xF433,
        "0xF433",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::BaseballBall",
        "Baseball Ball"
    },
    {
        0xF434,
        "0xF434",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::BasketballBall",
        "Basketball Ball"
    },
    {
        0xF2CD,
        "0xF2CD",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Bath",
        "Bath"
    },
    {
        0xF244,
        "0xF244",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::BatteryEmpty",
        "Battery Empty"
    },
    {
        0xF240,
        "0xF240",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::BatteryFull",
        "Battery Full"
    },
    {
        0xF242,
        "0xF242",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::BatteryHalf",
        "Battery Half"
    },
    {
        0xF243,
        "0xF243",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::BatteryQuarter",
        "Battery Quarter"
    },
    {
        0xF241,
        "0xF241",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::BatteryThreeQuarters",
        "Battery Three Quarters"
    },
    {
        0xF236,
        "0xF236",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Bed",
        "Bed"
    },
    {
        0xF0FC,
        "0xF0FC",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Beer",
        "Beer"
    },
    {
        0xF0F3,
        "0xF0F3",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Bell",
        "Bell"
    },
    {
        0xF1F6,
        "0xF1F6",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::BellSlash",
        "Bell Slash"
    },
    {
        0xF55B,
        "0xF55B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::BezierCurve",
        "Bezier Curve"
    },
    {
        0xF206,
        "0xF206",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Bicycle",
        "Bicycle"
    },
    {
        0xF1E5,
        "0xF1E5",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Binoculars",
        "Binoculars"
    },
    {
        0xF1FD,
        "0xF1FD",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::BirthdayCake",
        "Birthday Cake"
    },
    {
        0xF517,
        "0xF517",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Blender",
        "Blender"
    },
    {
        0xF29D,
        "0xF29D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Blind",
        "Blind"
    },
    {
        0xF032,
        "0xF032",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Bold",
        "Bold"
    },
    {
        0xF0E7,
        "0xF0E7",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Bolt",
        "Bolt"
    },
    {
        0xF1E2,
        "0xF1E2",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Bomb",
        "Bomb"
    },
    {
        0xF55C,
        "0xF55C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Bong",
        "Bong"
    },
    {
        0xF02D,
        "0xF02D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Book",
        "Book"
    },
    {
        0xF518,
        "0xF518",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::BookOpen",
        "Book Open"
    },
    {
        0xF02E,
        "0xF02E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Bookmark",
        "Bookmark"
    },
    {
        0xF436,
        "0xF436",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::BowlingBall",
        "Bowling Ball"
    },
    {
        0xF466,
        "0xF466",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Box",
        "Box"
    },
    {
        0xF49E,
        "0xF49E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::BoxOpen",
        "Box Open"
    },
    {
        0xF468,
        "0xF468",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Boxes",
        "Boxes"
    },
    {
        0xF2A1,
        "0xF2A1",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Braille",
        "Braille"
    },
    {
        0xF0B1,
        "0xF0B1",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Briefcase",
        "Briefcase"
    },
    {
        0xF469,
        "0xF469",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::BriefcaseMedical",
        "Briefcase Medical"
    },
    {
        0xF519,
        "0xF519",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::BroadcastTower",
        "Broadcast Tower"
    },
    {
        0xF51A,
        "0xF51A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Broom",
        "Broom"
    },
    {
        0xF55D,
        "0xF55D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Brush",
        "Brush"
    },
    {
        0xF188,
        "0xF188",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Bug",
        "Bug"
    },
    {
        0xF1AD,
        "0xF1AD",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Building",
        "Building"
    },
    {
        0xF0A1,
        "0xF0A1",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Bullhorn",
        "Bullhorn"
    },
    {
        0xF140,
        "0xF140",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Bullseye",
        "Bullseye"
    },
    {
        0xF46A,
        "0xF46A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Burn",
        "Burn"
    },
    {
        0xF207,
        "0xF207",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Bus",
        "Bus"
    },
    {
        0xF55E,
        "0xF55E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::BusAlt",
        "Bus Alt"
    },
    {
        0xF1EC,
        "0xF1EC",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Calculator",
        "Calculator"
    },
    {
        0xF133,
        "0xF133",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Calendar",
        "Calendar"
    },
    {
        0xF073,
        "0xF073",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CalendarAlt",
        "Calendar Alt"
    },
    {
        0xF274,
        "0xF274",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CalendarCheck",
        "Calendar Check"
    },
    {
        0xF272,
        "0xF272",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CalendarMinus",
        "Calendar Minus"
    },
    {
        0xF271,
        "0xF271",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CalendarPlus",
        "Calendar Plus"
    },
    {
        0xF273,
        "0xF273",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CalendarTimes",
        "Calendar Times"
    },
    {
        0xF030,
        "0xF030",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Camera",
        "Camera"
    },
    {
        0xF083,
        "0xF083",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CameraRetro",
        "Camera Retro"
    },
    {
        0xF55F,
        "0xF55F",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Cannabis",
        "Cannabis"
    },
    {
        0xF46B,
        "0xF46B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Capsules",
        "Capsules"
    },
    {
        0xF1B9,
        "0xF1B9",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Car",
        "Car"
    },
    {
        0xF0D7,
        "0xF0D7",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CaretDown",
        "Caret Down"
    },
    {
        0xF0D9,
        "0xF0D9",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CaretLeft",
        "Caret Left"
    },
    {
        0xF0DA,
        "0xF0DA",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CaretRight",
        "Caret Right"
    },
    {
        0xF150,
        "0xF150",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CaretSquareDown",
        "Caret Square Down"
    },
    {
        0xF191,
        "0xF191",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CaretSquareLeft",
        "Caret Square Left"
    },
    {
        0xF152,
        "0xF152",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CaretSquareRight",
        "Caret Square Right"
    },
    {
        0xF151,
        "0xF151",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CaretSquareUp",
        "Caret Square Up"
    },
    {
        0xF0D8,
        "0xF0D8",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CaretUp",
        "Caret Up"
    },
    {
        0xF218,
        "0xF218",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CartArrowDown",
        "Cart Arrow Down"
    },
    {
        0xF217,
        "0xF217",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CartPlus",
        "Cart Plus"
    },
    {
        0xF0A3,
        "0xF0A3",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Certificate",
        "Certificate"
    },
    {
        0xF51B,
        "0xF51B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Chalkboard",
        "Chalkboard"
    },
    {
        0xF51C,
        "0xF51C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ChalkboardTeacher",
        "Chalkboard Teacher"
    },
    {
        0xF1FE,
        "0xF1FE",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ChartArea",
        "Chart Area"
    },
    {
        0xF080,
        "0xF080",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ChartBar",
        "Chart Bar"
    },
    {
        0xF201,
        "0xF201",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ChartLine",
        "Chart Line"
    },
    {
        0xF200,
        "0xF200",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ChartPie",
        "Chart Pie"
    },
    {
        0xF00C,
        "0xF00C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Check",
        "Check"
    },
    {
        0xF058,
        "0xF058",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CheckCircle",
        "Check Circle"
    },
    {
        0xF560,
        "0xF560",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CheckDouble",
        "Check Double"
    },
    {
        0xF14A,
        "0xF14A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CheckSquare",
        "Check Square"
    },
    {
        0xF439,
        "0xF439",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Chess",
        "Chess"
    },
    {
        0xF43A,
        "0xF43A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ChessBishop",
        "Chess Bishop"
    },
    {
        0xF43C,
        "0xF43C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ChessBoard",
        "Chess Board"
    },
    {
        0xF43F,
        "0xF43F",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ChessKing",
        "Chess King"
    },
    {
        0xF441,
        "0xF441",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ChessKnight",
        "Chess Knight"
    },
    {
        0xF443,
        "0xF443",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ChessPawn",
        "Chess Pawn"
    },
    {
        0xF445,
        "0xF445",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ChessQueen",
        "Chess Queen"
    },
    {
        0xF447,
        "0xF447",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ChessRook",
        "Chess Rook"
    },
    {
        0xF13A,
        "0xF13A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ChevronCircleDown",
        "Chevron Circle Down"
    },
    {
        0xF137,
        "0xF137",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ChevronCircleLeft",
        "Chevron Circle Left"
    },
    {
        0xF138,
        "0xF138",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ChevronCircleRight",
        "Chevron Circle Right"
    },
    {
        0xF139,
        "0xF139",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ChevronCircleUp",
        "Chevron Circle Up"
    },
    {
        0xF078,
        "0xF078",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ChevronDown",
        "Chevron Down"
    },
    {
        0xF053,
        "0xF053",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ChevronLeft",
        "Chevron Left"
    },
    {
        0xF054,
        "0xF054",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ChevronRight",
        "Chevron Right"
    },
    {
        0xF077,
        "0xF077",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ChevronUp",
        "Chevron Up"
    },
    {
        0xF1AE,
        "0xF1AE",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Child",
        "Child"
    },
    {
        0xF51D,
        "0xF51D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Church",
        "Church"
    },
    {
        0xF111,
        "0xF111",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Circle",
        "Circle"
    },
    {
        0xF1CE,
        "0xF1CE",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CircleNotch",
        "Circle Notch"
    },
    {
        0xF328,
        "0xF328",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Clipboard",
        "Clipboard"
    },
    {
        0xF46C,
        "0xF46C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ClipboardCheck",
        "Clipboard Check"
    },
    {
        0xF46D,
        "0xF46D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ClipboardList",
        "Clipboard List"
    },
    {
        0xF017,
        "0xF017",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Clock",
        "Clock"
    },
    {
        0xF24D,
        "0xF24D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Clone",
        "Clone"
    },
    {
        0xF20A,
        "0xF20A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ClosedCaptioning",
        "Closed Captioning"
    },
    {
        0xF0C2,
        "0xF0C2",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Cloud",
        "Cloud"
    },
    {
        0xF381,
        "0xF381",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CloudDownloadAlt",
        "Cloud Download Alt"
    },
    {
        0xF382,
        "0xF382",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CloudUploadAlt",
        "Cloud Upload Alt"
    },
    {
        0xF561,
        "0xF561",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Cocktail",
        "Cocktail"
    },
    {
        0xF121,
        "0xF121",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Code",
        "Code"
    },
    {
        0xF126,
        "0xF126",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CodeBranch",
        "Code Branch"
    },
    {
        0xF0F4,
        "0xF0F4",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Coffee",
        "Coffee"
    },
    {
        0xF013,
        "0xF013",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Cog",
        "Cog"
    },
    {
        0xF085,
        "0xF085",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Cogs",
        "Cogs"
    },
    {
        0xF51E,
        "0xF51E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Coins",
        "Coins"
    },
    {
        0xF0DB,
        "0xF0DB",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Columns",
        "Columns"
    },
    {
        0xF075,
        "0xF075",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Comment",
        "Comment"
    },
    {
        0xF27A,
        "0xF27A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CommentAlt",
        "Comment Alt"
    },
    {
        0xF4AD,
        "0xF4AD",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CommentDots",
        "Comment Dots"
    },
    {
        0xF4B3,
        "0xF4B3",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CommentSlash",
        "Comment Slash"
    },
    {
        0xF086,
        "0xF086",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Comments",
        "Comments"
    },
    {
        0xF51F,
        "0xF51F",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CompactDisc",
        "Compact Disc"
    },
    {
        0xF14E,
        "0xF14E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Compass",
        "Compass"
    },
    {
        0xF066,
        "0xF066",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Compress",
        "Compress"
    },
    {
        0xF562,
        "0xF562",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ConciergeBell",
        "Concierge Bell"
    },
    {
        0xF563,
        "0xF563",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Cookie",
        "Cookie"
    },
    {
        0xF564,
        "0xF564",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CookieBite",
        "Cookie Bite"
    },
    {
        0xF0C5,
        "0xF0C5",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Copy",
        "Copy"
    },
    {
        0xF1F9,
        "0xF1F9",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Copyright",
        "Copyright"
    },
    {
        0xF4B8,
        "0xF4B8",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Couch",
        "Couch"
    },
    {
        0xF09D,
        "0xF09D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CreditCard",
        "Credit Card"
    },
    {
        0xF125,
        "0xF125",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Crop",
        "Crop"
    },
    {
        0xF565,
        "0xF565",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::CropAlt",
        "Crop Alt"
    },
    {
        0xF05B,
        "0xF05B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Crosshairs",
        "Crosshairs"
    },
    {
        0xF520,
        "0xF520",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Crow",
        "Crow"
    },
    {
        0xF521,
        "0xF521",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Crown",
        "Crown"
    },
    {
        0xF1B2,
        "0xF1B2",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Cube",
        "Cube"
    },
    {
        0xF1B3,
        "0xF1B3",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Cubes",
        "Cubes"
    },
    {
        0xF0C4,
        "0xF0C4",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Cut",
        "Cut"
    },
    {
        0xF1C0,
        "0xF1C0",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Database",
        "Database"
    },
    {
        0xF2A4,
        "0xF2A4",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Deaf",
        "Deaf"
    },
    {
        0xF108,
        "0xF108",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Desktop",
        "Desktop"
    },
    {
        0xF470,
        "0xF470",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Diagnoses",
        "Diagnoses"
    },
    {
        0xF522,
        "0xF522",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Dice",
        "Dice"
    },
    {
        0xF523,
        "0xF523",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::DiceFive",
        "Dice Five"
    },
    {
        0xF524,
        "0xF524",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::DiceFour",
        "Dice Four"
    },
    {
        0xF525,
        "0xF525",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::DiceOne",
        "Dice One"
    },
    {
        0xF526,
        "0xF526",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::DiceSix",
        "Dice Six"
    },
    {
        0xF527,
        "0xF527",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::DiceThree",
        "Dice Three"
    },
    {
        0xF528,
        "0xF528",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::DiceTwo",
        "Dice Two"
    },
    {
        0xF566,
        "0xF566",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::DigitalTachograph",
        "Digital Tachograph"
    },
    {
        0xF529,
        "0xF529",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Divide",
        "Divide"
    },
    {
        0xF567,
        "0xF567",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Dizzy",
        "Dizzy"
    },
    {
        0xF471,
        "0xF471",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Dna",
        "Dna"
    },
    {
        0xF155,
        "0xF155",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::DollarSign",
        "Dollar Sign"
    },
    {
        0xF472,
        "0xF472",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Dolly",
        "Dolly"
    },
    {
        0xF474,
        "0xF474",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::DollyFlatbed",
        "Dolly Flatbed"
    },
    {
        0xF4B9,
        "0xF4B9",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Donate",
        "Donate"
    },
    {
        0xF52A,
        "0xF52A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::DoorClosed",
        "Door Closed"
    },
    {
        0xF52B,
        "0xF52B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::DoorOpen",
        "Door Open"
    },
    {
        0xF192,
        "0xF192",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::DotCircle",
        "Dot Circle"
    },
    {
        0xF4BA,
        "0xF4BA",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Dove",
        "Dove"
    },
    {
        0xF019,
        "0xF019",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Download",
        "Download"
    },
    {
        0xF568,
        "0xF568",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::DraftingCompass",
        "Drafting Compass"
    },
    {
        0xF569,
        "0xF569",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Drum",
        "Drum"
    },
    {
        0xF56A,
        "0xF56A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::DrumSteelpan",
        "Drum Steelpan"
    },
    {
        0xF44B,
        "0xF44B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Dumbbell",
        "Dumbbell"
    },
    {
        0xF044,
        "0xF044",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Edit",
        "Edit"
    },
    {
        0xF052,
        "0xF052",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Eject",
        "Eject"
    },
    {
        0xF141,
        "0xF141",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::EllipsisH",
        "Ellipsis H"
    },
    {
        0xF142,
        "0xF142",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::EllipsisV",
        "Ellipsis V"
    },
    {
        0xF0E0,
        "0xF0E0",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Envelope",
        "Envelope"
    },
    {
        0xF2B6,
        "0xF2B6",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::EnvelopeOpen",
        "Envelope Open"
    },
    {
        0xF199,
        "0xF199",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::EnvelopeSquare",
        "Envelope Square"
    },
    {
        0xF52C,
        "0xF52C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Equals",
        "Equals"
    },
    {
        0xF12D,
        "0xF12D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Eraser",
        "Eraser"
    },
    {
        0xF153,
        "0xF153",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::EuroSign",
        "Euro Sign"
    },
    {
        0xF362,
        "0xF362",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ExchangeAlt",
        "Exchange Alt"
    },
    {
        0xF12A,
        "0xF12A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Exclamation",
        "Exclamation"
    },
    {
        0xF06A,
        "0xF06A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ExclamationCircle",
        "Exclamation Circle"
    },
    {
        0xF071,
        "0xF071",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ExclamationTriangle",
        "Exclamation Triangle"
    },
    {
        0xF065,
        "0xF065",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Expand",
        "Expand"
    },
    {
        0xF31E,
        "0xF31E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ExpandArrowsAlt",
        "Expand Arrows Alt"
    },
    {
        0xF35D,
        "0xF35D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ExternalLinkAlt",
        "External Link Alt"
    },
    {
        0xF360,
        "0xF360",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ExternalLinkSquareAlt",
        "External Link Square Alt"
    },
    {
        0xF06E,
        "0xF06E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Eye",
        "Eye"
    },
    {
        0xF1FB,
        "0xF1FB",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::EyeDropper",
        "Eye Dropper"
    },
    {
        0xF070,
        "0xF070",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::EyeSlash",
        "Eye Slash"
    },
    {
        0xF049,
        "0xF049",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FastBackward",
        "Fast Backward"
    },
    {
        0xF050,
        "0xF050",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FastForward",
        "Fast Forward"
    },
    {
        0xF1AC,
        "0xF1AC",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Fax",
        "Fax"
    },
    {
        0xF52D,
        "0xF52D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Feather",
        "Feather"
    },
    {
        0xF56B,
        "0xF56B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FeatherAlt",
        "Feather Alt"
    },
    {
        0xF182,
        "0xF182",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Female",
        "Female"
    },
    {
        0xF0FB,
        "0xF0FB",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FighterJet",
        "Fighter Jet"
    },
    {
        0xF15B,
        "0xF15B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::File",
        "File"
    },
    {
        0xF15C,
        "0xF15C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FileAlt",
        "File Alt"
    },
    {
        0xF1C6,
        "0xF1C6",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FileArchive",
        "File Archive"
    },
    {
        0xF1C7,
        "0xF1C7",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FileAudio",
        "File Audio"
    },
    {
        0xF1C9,
        "0xF1C9",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FileCode",
        "File Code"
    },
    {
        0xF56C,
        "0xF56C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FileContract",
        "File Contract"
    },
    {
        0xF56D,
        "0xF56D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FileDownload",
        "File Download"
    },
    {
        0xF1C3,
        "0xF1C3",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FileExcel",
        "File Excel"
    },
    {
        0xF56E,
        "0xF56E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FileExport",
        "File Export"
    },
    {
        0xF1C5,
        "0xF1C5",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FileImage",
        "File Image"
    },
    {
        0xF56F,
        "0xF56F",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FileImport",
        "File Import"
    },
    {
        0xF570,
        "0xF570",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FileInvoice",
        "File Invoice"
    },
    {
        0xF571,
        "0xF571",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FileInvoiceDollar",
        "File Invoice Dollar"
    },
    {
        0xF477,
        "0xF477",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FileMedical",
        "File Medical"
    },
    {
        0xF478,
        "0xF478",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FileMedicalAlt",
        "File Medical Alt"
    },
    {
        0xF1C1,
        "0xF1C1",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FilePdf",
        "File Pdf"
    },
    {
        0xF1C4,
        "0xF1C4",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FilePowerpoint",
        "File Powerpoint"
    },
    {
        0xF572,
        "0xF572",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FilePrescription",
        "File Prescription"
    },
    {
        0xF573,
        "0xF573",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FileSignature",
        "File Signature"
    },
    {
        0xF574,
        "0xF574",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FileUpload",
        "File Upload"
    },
    {
        0xF1C8,
        "0xF1C8",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FileVideo",
        "File Video"
    },
    {
        0xF1C2,
        "0xF1C2",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FileWord",
        "File Word"
    },
    {
        0xF575,
        "0xF575",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Fill",
        "Fill"
    },
    {
        0xF576,
        "0xF576",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FillDrip",
        "Fill Drip"
    },
    {
        0xF008,
        "0xF008",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Film",
        "Film"
    },
    {
        0xF0B0,
        "0xF0B0",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Filter",
        "Filter"
    },
    {
        0xF577,
        "0xF577",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Fingerprint",
        "Fingerprint"
    },
    {
        0xF06D,
        "0xF06D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Fire",
        "Fire"
    },
    {
        0xF134,
        "0xF134",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FireExtinguisher",
        "Fire Extinguisher"
    },
    {
        0xF479,
        "0xF479",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FirstAid",
        "First Aid"
    },
    {
        0xF578,
        "0xF578",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Fish",
        "Fish"
    },
    {
        0xF024,
        "0xF024",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Flag",
        "Flag"
    },
    {
        0xF11E,
        "0xF11E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FlagCheckered",
        "Flag Checkered"
    },
    {
        0xF0C3,
        "0xF0C3",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Flask",
        "Flask"
    },
    {
        0xF579,
        "0xF579",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Flushed",
        "Flushed"
    },
    {
        0xF07B,
        "0xF07B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Folder",
        "Folder"
    },
    {
        0xF07C,
        "0xF07C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FolderOpen",
        "Folder Open"
    },
    {
        0xF031,
        "0xF031",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Font",
        "Font"
    },
    {
        0xF4E6,
        "0xF4E6",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FontAwesomeLogoFull",
        "Font Awesome Logo Full"
    },
    {
        0xF44E,
        "0xF44E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FootballBall",
        "Football Ball"
    },
    {
        0xF04E,
        "0xF04E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Forward",
        "Forward"
    },
    {
        0xF52E,
        "0xF52E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Frog",
        "Frog"
    },
    {
        0xF119,
        "0xF119",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Frown",
        "Frown"
    },
    {
        0xF57A,
        "0xF57A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::FrownOpen",
        "Frown Open"
    },
    {
        0xF1E3,
        "0xF1E3",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Futbol",
        "Futbol"
    },
    {
        0xF11B,
        "0xF11B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Gamepad",
        "Gamepad"
    },
    {
        0xF52F,
        "0xF52F",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GasPump",
        "Gas Pump"
    },
    {
        0xF0E3,
        "0xF0E3",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Gavel",
        "Gavel"
    },
    {
        0xF3A5,
        "0xF3A5",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Gem",
        "Gem"
    },
    {
        0xF22D,
        "0xF22D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Genderless",
        "Genderless"
    },
    {
        0xF06B,
        "0xF06B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Gift",
        "Gift"
    },
    {
        0xF000,
        "0xF000",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GlassMartini",
        "Glass Martini"
    },
    {
        0xF57B,
        "0xF57B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GlassMartiniAlt",
        "Glass Martini Alt"
    },
    {
        0xF530,
        "0xF530",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Glasses",
        "Glasses"
    },
    {
        0xF0AC,
        "0xF0AC",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Globe",
        "Globe"
    },
    {
        0xF57C,
        "0xF57C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GlobeAfrica",
        "Globe Africa"
    },
    {
        0xF57D,
        "0xF57D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GlobeAmericas",
        "Globe Americas"
    },
    {
        0xF57E,
        "0xF57E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GlobeAsia",
        "Globe Asia"
    },
    {
        0xF450,
        "0xF450",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GolfBall",
        "Golf Ball"
    },
    {
        0xF19D,
        "0xF19D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GraduationCap",
        "Graduation Cap"
    },
    {
        0xF531,
        "0xF531",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GreaterThan",
        "Greater Than"
    },
    {
        0xF532,
        "0xF532",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GreaterThanEqual",
        "Greater Than Equal"
    },
    {
        0xF57F,
        "0xF57F",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Grimace",
        "Grimace"
    },
    {
        0xF580,
        "0xF580",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Grin",
        "Grin"
    },
    {
        0xF581,
        "0xF581",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GrinAlt",
        "Grin Alt"
    },
    {
        0xF582,
        "0xF582",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GrinBeam",
        "Grin Beam"
    },
    {
        0xF583,
        "0xF583",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GrinBeamSweat",
        "Grin Beam Sweat"
    },
    {
        0xF584,
        "0xF584",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GrinHearts",
        "Grin Hearts"
    },
    {
        0xF585,
        "0xF585",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GrinSquint",
        "Grin Squint"
    },
    {
        0xF586,
        "0xF586",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GrinSquintTears",
        "Grin Squint Tears"
    },
    {
        0xF587,
        "0xF587",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GrinStars",
        "Grin Stars"
    },
    {
        0xF588,
        "0xF588",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GrinTears",
        "Grin Tears"
    },
    {
        0xF589,
        "0xF589",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GrinTongue",
        "Grin Tongue"
    },
    {
        0xF58A,
        "0xF58A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GrinTongueSquint",
        "Grin Tongue Squint"
    },
    {
        0xF58B,
        "0xF58B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GrinTongueWink",
        "Grin Tongue Wink"
    },
    {
        0xF58C,
        "0xF58C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GrinWink",
        "Grin Wink"
    },
    {
        0xF58D,
        "0xF58D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GripHorizontal",
        "Grip Horizontal"
    },
    {
        0xF58E,
        "0xF58E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::GripVertical",
        "Grip Vertical"
    },
    {
        0xF0FD,
        "0xF0FD",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HSquare",
        "H Square"
    },
    {
        0xF4BD,
        "0xF4BD",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HandHolding",
        "Hand Holding"
    },
    {
        0xF4BE,
        "0xF4BE",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HandHoldingHeart",
        "Hand Holding Heart"
    },
    {
        0xF4C0,
        "0xF4C0",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HandHoldingUsd",
        "Hand Holding Usd"
    },
    {
        0xF258,
        "0xF258",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HandLizard",
        "Hand Lizard"
    },
    {
        0xF256,
        "0xF256",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HandPaper",
        "Hand Paper"
    },
    {
        0xF25B,
        "0xF25B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HandPeace",
        "Hand Peace"
    },
    {
        0xF0A7,
        "0xF0A7",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HandPointDown",
        "Hand Point Down"
    },
    {
        0xF0A5,
        "0xF0A5",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HandPointLeft",
        "Hand Point Left"
    },
    {
        0xF0A4,
        "0xF0A4",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HandPointRight",
        "Hand Point Right"
    },
    {
        0xF0A6,
        "0xF0A6",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HandPointUp",
        "Hand Point Up"
    },
    {
        0xF25A,
        "0xF25A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HandPointer",
        "Hand Pointer"
    },
    {
        0xF255,
        "0xF255",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HandRock",
        "Hand Rock"
    },
    {
        0xF257,
        "0xF257",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HandScissors",
        "Hand Scissors"
    },
    {
        0xF259,
        "0xF259",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HandSpock",
        "Hand Spock"
    },
    {
        0xF4C2,
        "0xF4C2",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Hands",
        "Hands"
    },
    {
        0xF4C4,
        "0xF4C4",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HandsHelping",
        "Hands Helping"
    },
    {
        0xF2B5,
        "0xF2B5",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Handshake",
        "Handshake"
    },
    {
        0xF292,
        "0xF292",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Hashtag",
        "Hashtag"
    },
    {
        0xF0A0,
        "0xF0A0",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Hdd",
        "Hdd"
    },
    {
        0xF1DC,
        "0xF1DC",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Heading",
        "Heading"
    },
    {
        0xF025,
        "0xF025",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Headphones",
        "Headphones"
    },
    {
        0xF58F,
        "0xF58F",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HeadphonesAlt",
        "Headphones Alt"
    },
    {
        0xF590,
        "0xF590",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Headset",
        "Headset"
    },
    {
        0xF004,
        "0xF004",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Heart",
        "Heart"
    },
    {
        0xF21E,
        "0xF21E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Heartbeat",
        "Heartbeat"
    },
    {
        0xF533,
        "0xF533",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Helicopter",
        "Helicopter"
    },
    {
        0xF591,
        "0xF591",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Highlighter",
        "Highlighter"
    },
    {
        0xF1DA,
        "0xF1DA",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::History",
        "History"
    },
    {
        0xF453,
        "0xF453",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HockeyPuck",
        "Hockey Puck"
    },
    {
        0xF015,
        "0xF015",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Home",
        "Home"
    },
    {
        0xF0F8,
        "0xF0F8",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Hospital",
        "Hospital"
    },
    {
        0xF47D,
        "0xF47D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HospitalAlt",
        "Hospital Alt"
    },
    {
        0xF47E,
        "0xF47E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HospitalSymbol",
        "Hospital Symbol"
    },
    {
        0xF593,
        "0xF593",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HotTub",
        "Hot Tub"
    },
    {
        0xF594,
        "0xF594",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Hotel",
        "Hotel"
    },
    {
        0xF254,
        "0xF254",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Hourglass",
        "Hourglass"
    },
    {
        0xF253,
        "0xF253",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HourglassEnd",
        "Hourglass End"
    },
    {
        0xF252,
        "0xF252",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HourglassHalf",
        "Hourglass Half"
    },
    {
        0xF251,
        "0xF251",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::HourglassStart",
        "Hourglass Start"
    },
    {
        0xF246,
        "0xF246",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ICursor",
        "I Cursor"
    },
    {
        0xF2C1,
        "0xF2C1",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::IdBadge",
        "Id Badge"
    },
    {
        0xF2C2,
        "0xF2C2",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::IdCard",
        "Id Card"
    },
    {
        0xF47F,
        "0xF47F",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::IdCardAlt",
        "Id Card Alt"
    },
    {
        0xF03E,
        "0xF03E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Image",
        "Image"
    },
    {
        0xF302,
        "0xF302",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Images",
        "Images"
    },
    {
        0xF01C,
        "0xF01C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Inbox",
        "Inbox"
    },
    {
        0xF03C,
        "0xF03C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Indent",
        "Indent"
    },
    {
        0xF275,
        "0xF275",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Industry",
        "Industry"
    },
    {
        0xF534,
        "0xF534",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Infinity",
        "Infinity"
    },
    {
        0xF129,
        "0xF129",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Info",
        "Info"
    },
    {
        0xF05A,
        "0xF05A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::InfoCircle",
        "Info Circle"
    },
    {
        0xF033,
        "0xF033",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Italic",
        "Italic"
    },
    {
        0xF595,
        "0xF595",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Joint",
        "Joint"
    },
    {
        0xF084,
        "0xF084",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Key",
        "Key"
    },
    {
        0xF11C,
        "0xF11C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Keyboard",
        "Keyboard"
    },
    {
        0xF596,
        "0xF596",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Kiss",
        "Kiss"
    },
    {
        0xF597,
        "0xF597",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::KissBeam",
        "Kiss Beam"
    },
    {
        0xF598,
        "0xF598",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::KissWinkHeart",
        "Kiss Wink Heart"
    },
    {
        0xF535,
        "0xF535",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::KiwiBird",
        "Kiwi Bird"
    },
    {
        0xF1AB,
        "0xF1AB",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Language",
        "Language"
    },
    {
        0xF109,
        "0xF109",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Laptop",
        "Laptop"
    },
    {
        0xF599,
        "0xF599",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Laugh",
        "Laugh"
    },
    {
        0xF59A,
        "0xF59A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::LaughBeam",
        "Laugh Beam"
    },
    {
        0xF59B,
        "0xF59B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::LaughSquint",
        "Laugh Squint"
    },
    {
        0xF59C,
        "0xF59C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::LaughWink",
        "Laugh Wink"
    },
    {
        0xF06C,
        "0xF06C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Leaf",
        "Leaf"
    },
    {
        0xF094,
        "0xF094",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Lemon",
        "Lemon"
    },
    {
        0xF536,
        "0xF536",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::LessThan",
        "Less Than"
    },
    {
        0xF537,
        "0xF537",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::LessThanEqual",
        "Less Than Equal"
    },
    {
        0xF3BE,
        "0xF3BE",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::LevelDownAlt",
        "Level Down Alt"
    },
    {
        0xF3BF,
        "0xF3BF",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::LevelUpAlt",
        "Level Up Alt"
    },
    {
        0xF1CD,
        "0xF1CD",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::LifeRing",
        "Life Ring"
    },
    {
        0xF0EB,
        "0xF0EB",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Lightbulb",
        "Lightbulb"
    },
    {
        0xF0C1,
        "0xF0C1",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Link",
        "Link"
    },
    {
        0xF195,
        "0xF195",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::LiraSign",
        "Lira Sign"
    },
    {
        0xF03A,
        "0xF03A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::List",
        "List"
    },
    {
        0xF022,
        "0xF022",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ListAlt",
        "List Alt"
    },
    {
        0xF0CB,
        "0xF0CB",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ListOl",
        "List Ol"
    },
    {
        0xF0CA,
        "0xF0CA",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ListUl",
        "List Ul"
    },
    {
        0xF124,
        "0xF124",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::LocationArrow",
        "Location Arrow"
    },
    {
        0xF023,
        "0xF023",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Lock",
        "Lock"
    },
    {
        0xF3C1,
        "0xF3C1",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::LockOpen",
        "Lock Open"
    },
    {
        0xF309,
        "0xF309",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::LongArrowAltDown",
        "Long Arrow Alt Down"
    },
    {
        0xF30A,
        "0xF30A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::LongArrowAltLeft",
        "Long Arrow Alt Left"
    },
    {
        0xF30B,
        "0xF30B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::LongArrowAltRight",
        "Long Arrow Alt Right"
    },
    {
        0xF30C,
        "0xF30C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::LongArrowAltUp",
        "Long Arrow Alt Up"
    },
    {
        0xF2A8,
        "0xF2A8",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::LowVision",
        "Low Vision"
    },
    {
        0xF59D,
        "0xF59D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::LuggageCart",
        "Luggage Cart"
    },
    {
        0xF0D0,
        "0xF0D0",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Magic",
        "Magic"
    },
    {
        0xF076,
        "0xF076",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Magnet",
        "Magnet"
    },
    {
        0xF183,
        "0xF183",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Male",
        "Male"
    },
    {
        0xF279,
        "0xF279",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Map",
        "Map"
    },
    {
        0xF59F,
        "0xF59F",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MapMarked",
        "Map Marked"
    },
    {
        0xF5A0,
        "0xF5A0",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MapMarkedAlt",
        "Map Marked Alt"
    },
    {
        0xF041,
        "0xF041",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MapMarker",
        "Map Marker"
    },
    {
        0xF3C5,
        "0xF3C5",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MapMarkerAlt",
        "Map Marker Alt"
    },
    {
        0xF276,
        "0xF276",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MapPin",
        "Map Pin"
    },
    {
        0xF277,
        "0xF277",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MapSigns",
        "Map Signs"
    },
    {
        0xF5A1,
        "0xF5A1",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Marker",
        "Marker"
    },
    {
        0xF222,
        "0xF222",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Mars",
        "Mars"
    },
    {
        0xF227,
        "0xF227",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MarsDouble",
        "Mars Double"
    },
    {
        0xF229,
        "0xF229",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MarsStroke",
        "Mars Stroke"
    },
    {
        0xF22B,
        "0xF22B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MarsStrokeH",
        "Mars Stroke H"
    },
    {
        0xF22A,
        "0xF22A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MarsStrokeV",
        "Mars Stroke V"
    },
    {
        0xF5A2,
        "0xF5A2",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Medal",
        "Medal"
    },
    {
        0xF0FA,
        "0xF0FA",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Medkit",
        "Medkit"
    },
    {
        0xF11A,
        "0xF11A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Meh",
        "Meh"
    },
    {
        0xF5A4,
        "0xF5A4",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MehBlank",
        "Meh Blank"
    },
    {
        0xF5A5,
        "0xF5A5",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MehRollingEyes",
        "Meh Rolling Eyes"
    },
    {
        0xF538,
        "0xF538",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Memory",
        "Memory"
    },
    {
        0xF223,
        "0xF223",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Mercury",
        "Mercury"
    },
    {
        0xF2DB,
        "0xF2DB",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Microchip",
        "Microchip"
    },
    {
        0xF130,
        "0xF130",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Microphone",
        "Microphone"
    },
    {
        0xF3C9,
        "0xF3C9",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MicrophoneAlt",
        "Microphone Alt"
    },
    {
        0xF539,
        "0xF539",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MicrophoneAltSlash",
        "Microphone Alt Slash"
    },
    {
        0xF131,
        "0xF131",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MicrophoneSlash",
        "Microphone Slash"
    },
    {
        0xF068,
        "0xF068",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Minus",
        "Minus"
    },
    {
        0xF056,
        "0xF056",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MinusCircle",
        "Minus Circle"
    },
    {
        0xF146,
        "0xF146",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MinusSquare",
        "Minus Square"
    },
    {
        0xF10B,
        "0xF10B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Mobile",
        "Mobile"
    },
    {
        0xF3CD,
        "0xF3CD",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MobileAlt",
        "Mobile Alt"
    },
    {
        0xF0D6,
        "0xF0D6",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MoneyBill",
        "Money Bill"
    },
    {
        0xF3D1,
        "0xF3D1",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MoneyBillAlt",
        "Money Bill Alt"
    },
    {
        0xF53A,
        "0xF53A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MoneyBillWave",
        "Money Bill Wave"
    },
    {
        0xF53B,
        "0xF53B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MoneyBillWaveAlt",
        "Money Bill Wave Alt"
    },
    {
        0xF53C,
        "0xF53C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MoneyCheck",
        "Money Check"
    },
    {
        0xF53D,
        "0xF53D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MoneyCheckAlt",
        "Money Check Alt"
    },
    {
        0xF5A6,
        "0xF5A6",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Monument",
        "Monument"
    },
    {
        0xF186,
        "0xF186",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Moon",
        "Moon"
    },
    {
        0xF5A7,
        "0xF5A7",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MortarPestle",
        "Mortar Pestle"
    },
    {
        0xF21C,
        "0xF21C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Motorcycle",
        "Motorcycle"
    },
    {
        0xF245,
        "0xF245",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::MousePointer",
        "Mouse Pointer"
    },
    {
        0xF001,
        "0xF001",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Music",
        "Music"
    },
    {
        0xF22C,
        "0xF22C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Neuter",
        "Neuter"
    },
    {
        0xF1EA,
        "0xF1EA",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Newspaper",
        "Newspaper"
    },
    {
        0xF53E,
        "0xF53E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::NotEqual",
        "Not Equal"
    },
    {
        0xF481,
        "0xF481",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::NotesMedical",
        "Notes Medical"
    },
    {
        0xF247,
        "0xF247",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ObjectGroup",
        "Object Group"
    },
    {
        0xF248,
        "0xF248",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ObjectUngroup",
        "Object Ungroup"
    },
    {
        0xF03B,
        "0xF03B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Outdent",
        "Outdent"
    },
    {
        0xF1FC,
        "0xF1FC",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PaintBrush",
        "Paint Brush"
    },
    {
        0xF5AA,
        "0xF5AA",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PaintRoller",
        "Paint Roller"
    },
    {
        0xF53F,
        "0xF53F",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Palette",
        "Palette"
    },
    {
        0xF482,
        "0xF482",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Pallet",
        "Pallet"
    },
    {
        0xF1D8,
        "0xF1D8",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PaperPlane",
        "Paper Plane"
    },
    {
        0xF0C6,
        "0xF0C6",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Paperclip",
        "Paperclip"
    },
    {
        0xF4CD,
        "0xF4CD",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ParachuteBox",
        "Parachute Box"
    },
    {
        0xF1DD,
        "0xF1DD",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Paragraph",
        "Paragraph"
    },
    {
        0xF540,
        "0xF540",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Parking",
        "Parking"
    },
    {
        0xF5AB,
        "0xF5AB",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Passport",
        "Passport"
    },
    {
        0xF0EA,
        "0xF0EA",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Paste",
        "Paste"
    },
    {
        0xF04C,
        "0xF04C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Pause",
        "Pause"
    },
    {
        0xF28B,
        "0xF28B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PauseCircle",
        "Pause Circle"
    },
    {
        0xF1B0,
        "0xF1B0",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Paw",
        "Paw"
    },
    {
        0xF304,
        "0xF304",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Pen",
        "Pen"
    },
    {
        0xF305,
        "0xF305",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PenAlt",
        "Pen Alt"
    },
    {
        0xF5AC,
        "0xF5AC",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PenFancy",
        "Pen Fancy"
    },
    {
        0xF5AD,
        "0xF5AD",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PenNib",
        "Pen Nib"
    },
    {
        0xF14B,
        "0xF14B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PenSquare",
        "Pen Square"
    },
    {
        0xF303,
        "0xF303",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PencilAlt",
        "Pencil Alt"
    },
    {
        0xF5AE,
        "0xF5AE",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PencilRuler",
        "Pencil Ruler"
    },
    {
        0xF4CE,
        "0xF4CE",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PeopleCarry",
        "People Carry"
    },
    {
        0xF295,
        "0xF295",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Percent",
        "Percent"
    },
    {
        0xF541,
        "0xF541",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Percentage",
        "Percentage"
    },
    {
        0xF095,
        "0xF095",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Phone",
        "Phone"
    },
    {
        0xF3DD,
        "0xF3DD",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PhoneSlash",
        "Phone Slash"
    },
    {
        0xF098,
        "0xF098",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PhoneSquare",
        "Phone Square"
    },
    {
        0xF2A0,
        "0xF2A0",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PhoneVolume",
        "Phone Volume"
    },
    {
        0xF4D3,
        "0xF4D3",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PiggyBank",
        "Piggy Bank"
    },
    {
        0xF484,
        "0xF484",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Pills",
        "Pills"
    },
    {
        0xF072,
        "0xF072",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Plane",
        "Plane"
    },
    {
        0xF5AF,
        "0xF5AF",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PlaneArrival",
        "Plane Arrival"
    },
    {
        0xF5B0,
        "0xF5B0",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PlaneDeparture",
        "Plane Departure"
    },
    {
        0xF04B,
        "0xF04B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Play",
        "Play"
    },
    {
        0xF144,
        "0xF144",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PlayCircle",
        "Play Circle"
    },
    {
        0xF1E6,
        "0xF1E6",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Plug",
        "Plug"
    },
    {
        0xF067,
        "0xF067",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Plus",
        "Plus"
    },
    {
        0xF055,
        "0xF055",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PlusCircle",
        "Plus Circle"
    },
    {
        0xF0FE,
        "0xF0FE",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PlusSquare",
        "Plus Square"
    },
    {
        0xF2CE,
        "0xF2CE",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Podcast",
        "Podcast"
    },
    {
        0xF2FE,
        "0xF2FE",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Poo",
        "Poo"
    },
    {
        0xF3E0,
        "0xF3E0",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Portrait",
        "Portrait"
    },
    {
        0xF154,
        "0xF154",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PoundSign",
        "Pound Sign"
    },
    {
        0xF011,
        "0xF011",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PowerOff",
        "Power Off"
    },
    {
        0xF5B1,
        "0xF5B1",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Prescription",
        "Prescription"
    },
    {
        0xF485,
        "0xF485",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PrescriptionBottle",
        "Prescription Bottle"
    },
    {
        0xF486,
        "0xF486",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PrescriptionBottleAlt",
        "Prescription Bottle Alt"
    },
    {
        0xF02F,
        "0xF02F",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Print",
        "Print"
    },
    {
        0xF487,
        "0xF487",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Procedures",
        "Procedures"
    },
    {
        0xF542,
        "0xF542",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ProjectDiagram",
        "Project Diagram"
    },
    {
        0xF12E,
        "0xF12E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::PuzzlePiece",
        "Puzzle Piece"
    },
    {
        0xF029,
        "0xF029",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Qrcode",
        "Qrcode"
    },
    {
        0xF128,
        "0xF128",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Question",
        "Question"
    },
    {
        0xF059,
        "0xF059",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::QuestionCircle",
        "Question Circle"
    },
    {
        0xF458,
        "0xF458",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Quidditch",
        "Quidditch"
    },
    {
        0xF10D,
        "0xF10D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::QuoteLeft",
        "Quote Left"
    },
    {
        0xF10E,
        "0xF10E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::QuoteRight",
        "Quote Right"
    },
    {
        0xF074,
        "0xF074",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Random",
        "Random"
    },
    {
        0xF543,
        "0xF543",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Receipt",
        "Receipt"
    },
    {
        0xF1B8,
        "0xF1B8",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Recycle",
        "Recycle"
    },
    {
        0xF01E,
        "0xF01E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Redo",
        "Redo"
    },
    {
        0xF2F9,
        "0xF2F9",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::RedoAlt",
        "Redo Alt"
    },
    {
        0xF25D,
        "0xF25D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Registered",
        "Registered"
    },
    {
        0xF3E5,
        "0xF3E5",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Reply",
        "Reply"
    },
    {
        0xF122,
        "0xF122",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ReplyAll",
        "Reply All"
    },
    {
        0xF079,
        "0xF079",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Retweet",
        "Retweet"
    },
    {
        0xF4D6,
        "0xF4D6",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Ribbon",
        "Ribbon"
    },
    {
        0xF018,
        "0xF018",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Road",
        "Road"
    },
    {
        0xF544,
        "0xF544",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Robot",
        "Robot"
    },
    {
        0xF135,
        "0xF135",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Rocket",
        "Rocket"
    },
    {
        0xF09E,
        "0xF09E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Rss",
        "Rss"
    },
    {
        0xF143,
        "0xF143",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::RssSquare",
        "Rss Square"
    },
    {
        0xF158,
        "0xF158",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::RubleSign",
        "Ruble Sign"
    },
    {
        0xF545,
        "0xF545",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Ruler",
        "Ruler"
    },
    {
        0xF546,
        "0xF546",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::RulerCombined",
        "Ruler Combined"
    },
    {
        0xF547,
        "0xF547",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::RulerHorizontal",
        "Ruler Horizontal"
    },
    {
        0xF548,
        "0xF548",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::RulerVertical",
        "Ruler Vertical"
    },
    {
        0xF156,
        "0xF156",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::RupeeSign",
        "Rupee Sign"
    },
    {
        0xF5B3,
        "0xF5B3",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SadCry",
        "Sad Cry"
    },
    {
        0xF5B4,
        "0xF5B4",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SadTear",
        "Sad Tear"
    },
    {
        0xF0C7,
        "0xF0C7",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Save",
        "Save"
    },
    {
        0xF549,
        "0xF549",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::School",
        "School"
    },
    {
        0xF54A,
        "0xF54A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Screwdriver",
        "Screwdriver"
    },
    {
        0xF002,
        "0xF002",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Search",
        "Search"
    },
    {
        0xF010,
        "0xF010",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SearchMinus",
        "Search Minus"
    },
    {
        0xF00E,
        "0xF00E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SearchPlus",
        "Search Plus"
    },
    {
        0xF4D8,
        "0xF4D8",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Seedling",
        "Seedling"
    },
    {
        0xF233,
        "0xF233",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Server",
        "Server"
    },
    {
        0xF064,
        "0xF064",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Share",
        "Share"
    },
    {
        0xF1E0,
        "0xF1E0",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ShareAlt",
        "Share Alt"
    },
    {
        0xF1E1,
        "0xF1E1",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ShareAltSquare",
        "Share Alt Square"
    },
    {
        0xF14D,
        "0xF14D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ShareSquare",
        "Share Square"
    },
    {
        0xF20B,
        "0xF20B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ShekelSign",
        "Shekel Sign"
    },
    {
        0xF3ED,
        "0xF3ED",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ShieldAlt",
        "Shield Alt"
    },
    {
        0xF21A,
        "0xF21A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Ship",
        "Ship"
    },
    {
        0xF48B,
        "0xF48B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ShippingFast",
        "Shipping Fast"
    },
    {
        0xF54B,
        "0xF54B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ShoePrints",
        "Shoe Prints"
    },
    {
        0xF290,
        "0xF290",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ShoppingBag",
        "Shopping Bag"
    },
    {
        0xF291,
        "0xF291",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ShoppingBasket",
        "Shopping Basket"
    },
    {
        0xF07A,
        "0xF07A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ShoppingCart",
        "Shopping Cart"
    },
    {
        0xF2CC,
        "0xF2CC",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Shower",
        "Shower"
    },
    {
        0xF5B6,
        "0xF5B6",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ShuttleVan",
        "Shuttle Van"
    },
    {
        0xF4D9,
        "0xF4D9",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Sign",
        "Sign"
    },
    {
        0xF2F6,
        "0xF2F6",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SignInAlt",
        "Sign In Alt"
    },
    {
        0xF2A7,
        "0xF2A7",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SignLanguage",
        "Sign Language"
    },
    {
        0xF2F5,
        "0xF2F5",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SignOutAlt",
        "Sign Out Alt"
    },
    {
        0xF012,
        "0xF012",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Signal",
        "Signal"
    },
    {
        0xF5B7,
        "0xF5B7",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Signature",
        "Signature"
    },
    {
        0xF0E8,
        "0xF0E8",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Sitemap",
        "Sitemap"
    },
    {
        0xF54C,
        "0xF54C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Skull",
        "Skull"
    },
    {
        0xF1DE,
        "0xF1DE",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SlidersH",
        "Sliders H"
    },
    {
        0xF118,
        "0xF118",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Smile",
        "Smile"
    },
    {
        0xF5B8,
        "0xF5B8",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SmileBeam",
        "Smile Beam"
    },
    {
        0xF4DA,
        "0xF4DA",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SmileWink",
        "Smile Wink"
    },
    {
        0xF48D,
        "0xF48D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Smoking",
        "Smoking"
    },
    {
        0xF54D,
        "0xF54D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SmokingBan",
        "Smoking Ban"
    },
    {
        0xF2DC,
        "0xF2DC",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Snowflake",
        "Snowflake"
    },
    {
        0xF5BA,
        "0xF5BA",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SolarPanel",
        "Solar Panel"
    },
    {
        0xF0DC,
        "0xF0DC",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Sort",
        "Sort"
    },
    {
        0xF15D,
        "0xF15D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SortAlphaDown",
        "Sort Alpha Down"
    },
    {
        0xF15E,
        "0xF15E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SortAlphaUp",
        "Sort Alpha Up"
    },
    {
        0xF160,
        "0xF160",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SortAmountDown",
        "Sort Amount Down"
    },
    {
        0xF161,
        "0xF161",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SortAmountUp",
        "Sort Amount Up"
    },
    {
        0xF0DD,
        "0xF0DD",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SortDown",
        "Sort Down"
    },
    {
        0xF162,
        "0xF162",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SortNumericDown",
        "Sort Numeric Down"
    },
    {
        0xF163,
        "0xF163",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SortNumericUp",
        "Sort Numeric Up"
    },
    {
        0xF0DE,
        "0xF0DE",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SortUp",
        "Sort Up"
    },
    {
        0xF5BB,
        "0xF5BB",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Spa",
        "Spa"
    },
    {
        0xF197,
        "0xF197",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SpaceShuttle",
        "Space Shuttle"
    },
    {
        0xF110,
        "0xF110",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Spinner",
        "Spinner"
    },
    {
        0xF5BC,
        "0xF5BC",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Splotch",
        "Splotch"
    },
    {
        0xF5BD,
        "0xF5BD",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SprayCan",
        "Spray Can"
    },
    {
        0xF0C8,
        "0xF0C8",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Square",
        "Square"
    },
    {
        0xF45C,
        "0xF45C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SquareFull",
        "Square Full"
    },
    {
        0xF5BF,
        "0xF5BF",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Stamp",
        "Stamp"
    },
    {
        0xF005,
        "0xF005",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Star",
        "Star"
    },
    {
        0xF089,
        "0xF089",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::StarHalf",
        "Star Half"
    },
    {
        0xF5C0,
        "0xF5C0",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::StarHalfAlt",
        "Star Half Alt"
    },
    {
        0xF048,
        "0xF048",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::StepBackward",
        "Step Backward"
    },
    {
        0xF051,
        "0xF051",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::StepForward",
        "Step Forward"
    },
    {
        0xF0F1,
        "0xF0F1",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Stethoscope",
        "Stethoscope"
    },
    {
        0xF249,
        "0xF249",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::StickyNote",
        "Sticky Note"
    },
    {
        0xF04D,
        "0xF04D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Stop",
        "Stop"
    },
    {
        0xF28D,
        "0xF28D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::StopCircle",
        "Stop Circle"
    },
    {
        0xF2F2,
        "0xF2F2",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Stopwatch",
        "Stopwatch"
    },
    {
        0xF54E,
        "0xF54E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Store",
        "Store"
    },
    {
        0xF54F,
        "0xF54F",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::StoreAlt",
        "Store Alt"
    },
    {
        0xF550,
        "0xF550",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Stream",
        "Stream"
    },
    {
        0xF21D,
        "0xF21D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::StreetView",
        "Street View"
    },
    {
        0xF0CC,
        "0xF0CC",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Strikethrough",
        "Strikethrough"
    },
    {
        0xF551,
        "0xF551",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Stroopwafel",
        "Stroopwafel"
    },
    {
        0xF12C,
        "0xF12C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Subscript",
        "Subscript"
    },
    {
        0xF239,
        "0xF239",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Subway",
        "Subway"
    },
    {
        0xF0F2,
        "0xF0F2",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Suitcase",
        "Suitcase"
    },
    {
        0xF5C1,
        "0xF5C1",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SuitcaseRolling",
        "Suitcase Rolling"
    },
    {
        0xF185,
        "0xF185",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Sun",
        "Sun"
    },
    {
        0xF12B,
        "0xF12B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Superscript",
        "Superscript"
    },
    {
        0xF5C2,
        "0xF5C2",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Surprise",
        "Surprise"
    },
    {
        0xF5C3,
        "0xF5C3",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Swatchbook",
        "Swatchbook"
    },
    {
        0xF5C4,
        "0xF5C4",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Swimmer",
        "Swimmer"
    },
    {
        0xF5C5,
        "0xF5C5",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SwimmingPool",
        "Swimming Pool"
    },
    {
        0xF021,
        "0xF021",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Sync",
        "Sync"
    },
    {
        0xF2F1,
        "0xF2F1",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::SyncAlt",
        "Sync Alt"
    },
    {
        0xF48E,
        "0xF48E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Syringe",
        "Syringe"
    },
    {
        0xF0CE,
        "0xF0CE",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Table",
        "Table"
    },
    {
        0xF45D,
        "0xF45D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::TableTennis",
        "Table Tennis"
    },
    {
        0xF10A,
        "0xF10A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Tablet",
        "Tablet"
    },
    {
        0xF3FA,
        "0xF3FA",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::TabletAlt",
        "Tablet Alt"
    },
    {
        0xF490,
        "0xF490",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Tablets",
        "Tablets"
    },
    {
        0xF3FD,
        "0xF3FD",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::TachometerAlt",
        "Tachometer Alt"
    },
    {
        0xF02B,
        "0xF02B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Tag",
        "Tag"
    },
    {
        0xF02C,
        "0xF02C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Tags",
        "Tags"
    },
    {
        0xF4DB,
        "0xF4DB",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Tape",
        "Tape"
    },
    {
        0xF0AE,
        "0xF0AE",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Tasks",
        "Tasks"
    },
    {
        0xF1BA,
        "0xF1BA",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Taxi",
        "Taxi"
    },
    {
        0xF120,
        "0xF120",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Terminal",
        "Terminal"
    },
    {
        0xF034,
        "0xF034",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::TextHeight",
        "Text Height"
    },
    {
        0xF035,
        "0xF035",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::TextWidth",
        "Text Width"
    },
    {
        0xF00A,
        "0xF00A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Th",
        "Th"
    },
    {
        0xF009,
        "0xF009",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ThLarge",
        "Th Large"
    },
    {
        0xF00B,
        "0xF00B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ThList",
        "Th List"
    },
    {
        0xF491,
        "0xF491",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Thermometer",
        "Thermometer"
    },
    {
        0xF2CB,
        "0xF2CB",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ThermometerEmpty",
        "Thermometer Empty"
    },
    {
        0xF2C7,
        "0xF2C7",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ThermometerFull",
        "Thermometer Full"
    },
    {
        0xF2C9,
        "0xF2C9",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ThermometerHalf",
        "Thermometer Half"
    },
    {
        0xF2CA,
        "0xF2CA",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ThermometerQuarter",
        "Thermometer Quarter"
    },
    {
        0xF2C8,
        "0xF2C8",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ThermometerThreeQuarters",
        "Thermometer Three Quarters"
    },
    {
        0xF165,
        "0xF165",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ThumbsDown",
        "Thumbs Down"
    },
    {
        0xF164,
        "0xF164",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ThumbsUp",
        "Thumbs Up"
    },
    {
        0xF08D,
        "0xF08D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Thumbtack",
        "Thumbtack"
    },
    {
        0xF3FF,
        "0xF3FF",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::TicketAlt",
        "Ticket Alt"
    },
    {
        0xF00D,
        "0xF00D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Times",
        "Times"
    },
    {
        0xF057,
        "0xF057",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::TimesCircle",
        "Times Circle"
    },
    {
        0xF043,
        "0xF043",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Tint",
        "Tint"
    },
    {
        0xF5C7,
        "0xF5C7",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::TintSlash",
        "Tint Slash"
    },
    {
        0xF5C8,
        "0xF5C8",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Tired",
        "Tired"
    },
    {
        0xF204,
        "0xF204",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ToggleOff",
        "Toggle Off"
    },
    {
        0xF205,
        "0xF205",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::ToggleOn",
        "Toggle On"
    },
    {
        0xF552,
        "0xF552",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Toolbox",
        "Toolbox"
    },
    {
        0xF5C9,
        "0xF5C9",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Tooth",
        "Tooth"
    },
    {
        0xF25C,
        "0xF25C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Trademark",
        "Trademark"
    },
    {
        0xF238,
        "0xF238",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Train",
        "Train"
    },
    {
        0xF224,
        "0xF224",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Transgender",
        "Transgender"
    },
    {
        0xF225,
        "0xF225",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::TransgenderAlt",
        "Transgender Alt"
    },
    {
        0xF1F8,
        "0xF1F8",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Trash",
        "Trash"
    },
    {
        0xF2ED,
        "0xF2ED",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::TrashAlt",
        "Trash Alt"
    },
    {
        0xF1BB,
        "0xF1BB",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Tree",
        "Tree"
    },
    {
        0xF091,
        "0xF091",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Trophy",
        "Trophy"
    },
    {
        0xF0D1,
        "0xF0D1",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Truck",
        "Truck"
    },
    {
        0xF4DE,
        "0xF4DE",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::TruckLoading",
        "Truck Loading"
    },
    {
        0xF4DF,
        "0xF4DF",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::TruckMoving",
        "Truck Moving"
    },
    {
        0xF553,
        "0xF553",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Tshirt",
        "Tshirt"
    },
    {
        0xF1E4,
        "0xF1E4",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Tty",
        "Tty"
    },
    {
        0xF26C,
        "0xF26C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Tv",
        "Tv"
    },
    {
        0xF0E9,
        "0xF0E9",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Umbrella",
        "Umbrella"
    },
    {
        0xF5CA,
        "0xF5CA",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UmbrellaBeach",
        "Umbrella Beach"
    },
    {
        0xF0CD,
        "0xF0CD",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Underline",
        "Underline"
    },
    {
        0xF0E2,
        "0xF0E2",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Undo",
        "Undo"
    },
    {
        0xF2EA,
        "0xF2EA",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UndoAlt",
        "Undo Alt"
    },
    {
        0xF29A,
        "0xF29A",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UniversalAccess",
        "Universal Access"
    },
    {
        0xF19C,
        "0xF19C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::University",
        "University"
    },
    {
        0xF127,
        "0xF127",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Unlink",
        "Unlink"
    },
    {
        0xF09C,
        "0xF09C",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Unlock",
        "Unlock"
    },
    {
        0xF13E,
        "0xF13E",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UnlockAlt",
        "Unlock Alt"
    },
    {
        0xF093,
        "0xF093",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Upload",
        "Upload"
    },
    {
        0xF007,
        "0xF007",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::User",
        "User"
    },
    {
        0xF406,
        "0xF406",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UserAlt",
        "User Alt"
    },
    {
        0xF4FA,
        "0xF4FA",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UserAltSlash",
        "User Alt Slash"
    },
    {
        0xF4FB,
        "0xF4FB",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UserAstronaut",
        "User Astronaut"
    },
    {
        0xF4FC,
        "0xF4FC",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UserCheck",
        "User Check"
    },
    {
        0xF2BD,
        "0xF2BD",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UserCircle",
        "User Circle"
    },
    {
        0xF4FD,
        "0xF4FD",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UserClock",
        "User Clock"
    },
    {
        0xF4FE,
        "0xF4FE",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UserCog",
        "User Cog"
    },
    {
        0xF4FF,
        "0xF4FF",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UserEdit",
        "User Edit"
    },
    {
        0xF500,
        "0xF500",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UserFriends",
        "User Friends"
    },
    {
        0xF501,
        "0xF501",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UserGraduate",
        "User Graduate"
    },
    {
        0xF502,
        "0xF502",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UserLock",
        "User Lock"
    },
    {
        0xF0F0,
        "0xF0F0",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UserMd",
        "User Md"
    },
    {
        0xF503,
        "0xF503",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UserMinus",
        "User Minus"
    },
    {
        0xF504,
        "0xF504",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UserNinja",
        "User Ninja"
    },
    {
        0xF234,
        "0xF234",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UserPlus",
        "User Plus"
    },
    {
        0xF21B,
        "0xF21B",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UserSecret",
        "User Secret"
    },
    {
        0xF505,
        "0xF505",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UserShield",
        "User Shield"
    },
    {
        0xF506,
        "0xF506",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UserSlash",
        "User Slash"
    },
    {
        0xF507,
        "0xF507",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UserTag",
        "User Tag"
    },
    {
        0xF508,
        "0xF508",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UserTie",
        "User Tie"
    },
    {
        0xF235,
        "0xF235",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UserTimes",
        "User Times"
    },
    {
        0xF0C0,
        "0xF0C0",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Users",
        "Users"
    },
    {
        0xF509,
        "0xF509",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UsersCog",
        "Users Cog"
    },
    {
        0xF2E5,
        "0xF2E5",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::UtensilSpoon",
        "Utensil Spoon"
    },
    {
        0xF2E7,
        "0xF2E7",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Utensils",
        "Utensils"
    },
    {
        0xF5CB,
        "0xF5CB",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::VectorSquare",
        "Vector Square"
    },
    {
        0xF221,
        "0xF221",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Venus",
        "Venus"
    },
    {
        0xF226,
        "0xF226",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::VenusDouble",
        "Venus Double"
    },
    {
        0xF228,
        "0xF228",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::VenusMars",
        "Venus Mars"
    },
    {
        0xF492,
        "0xF492",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Vial",
        "Vial"
    },
    {
        0xF493,
        "0xF493",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Vials",
        "Vials"
    },
    {
        0xF03D,
        "0xF03D",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Video",
        "Video"
    },
    {
        0xF4E2,
        "0xF4E2",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::VideoSlash",
        "Video Slash"
    },
    {
        0xF45F,
        "0xF45F",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::VolleyballBall",
        "Volleyball Ball"
    },
    {
        0xF027,
        "0xF027",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::VolumeDown",
        "Volume Down"
    },
    {
        0xF026,
        "0xF026",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::VolumeOff",
        "Volume Off"
    },
    {
        0xF028,
        "0xF028",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::VolumeUp",
        "Volume Up"
    },
    {
        0xF554,
        "0xF554",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Walking",
        "Walking"
    },
    {
        0xF555,
        "0xF555",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Wallet",
        "Wallet"
    },
    {
        0xF494,
        "0xF494",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Warehouse",
        "Warehouse"
    },
    {
        0xF496,
        "0xF496",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Weight",
        "Weight"
    },
    {
        0xF5CD,
        "0xF5CD",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::WeightHanging",
        "Weight Hanging"
    },
    {
        0xF193,
        "0xF193",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Wheelchair",
        "Wheelchair"
    },
    {
        0xF1EB,
        "0xF1EB",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Wifi",
        "Wifi"
    },
    {
        0xF410,
        "0xF410",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::WindowClose",
        "Window Close"
    },
    {
        0xF2D0,
        "0xF2D0",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::WindowMaximize",
        "Window Maximize"
    },
    {
        0xF2D1,
        "0xF2D1",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::WindowMinimize",
        "Window Minimize"
    },
    {
        0xF2D2,
        "0xF2D2",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::WindowRestore",
        "Window Restore"
    },
    {
        0xF4E3,
        "0xF4E3",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::WineGlass",
        "Wine Glass"
    },
    {
        0xF5CE,
        "0xF5CE",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::WineGlassAlt",
        "Wine Glass Alt"
    },
    {
        0xF159,
        "0xF159",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::WonSign",
        "Won Sign"
    },
    {
        0xF0AD,
        "0xF0AD",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::Wrench",
        "Wrench"
    },
    {
        0xF497,
        "0xF497",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::XRay",
        "X Ray"
    },
    {
        0xF157,
        "0xF157",
        IconFontFamily::FontAwesome,
        "Font Awesome",
        "FAIcon::YenSign",
        "Yen Sign"
    }
};

inline QIcon getIcon(const IconInfo *iconInfo,
                     const QColor &col = {},
                     const int size = -1) {
    if (iconInfo->m_font == IconFontFamily::Material) {
        return getIcon(static_cast<MatIcon>(iconInfo->m_code), col, size);
    }  else if (iconInfo->m_font == IconFontFamily::FontAwesome) {
        return getIcon(static_cast<FAIcon>(iconInfo->m_code), col, size);
    }
    return getIcon(static_cast<FABrandIcon>(iconInfo->m_code), col, size);
}
}
