/* NetworkManager -- Network link manager
 *
 * Dan Williams <dcbw@redhat.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * (C) Copyright 2004 Red Hat, Inc.
 */

#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

/*
 * dbus services details
 */
#define	NM_DBUS_SERVICE			"org.freedesktop.NetworkManager"

#define	NM_DBUS_PATH				        "/org/freedesktop/NetworkManager"
#define	NM_DBUS_INTERFACE			        "org.freedesktop.NetworkManager"
#define	NM_DBUS_INTERFACE_DEVICE	        NM_DBUS_INTERFACE ".Device"
#define NM_DBUS_INTERFACE_DEVICE_WIRED      NM_DBUS_INTERFACE_DEVICE ".Wired"
#define NM_DBUS_INTERFACE_DEVICE_WIRELESS   NM_DBUS_INTERFACE_DEVICE ".Wireless"
#define NM_DBUS_PATH_ACCESS_POINT           NM_DBUS_PATH "/AccessPoint"
#define NM_DBUS_INTERFACE_ACCESS_POINT      NM_DBUS_INTERFACE ".AccessPoint"
#define NM_DBUS_INTERFACE_SERIAL_DEVICE     NM_DBUS_INTERFACE_DEVICE ".Serial"
#define NM_DBUS_INTERFACE_GSM_DEVICE        NM_DBUS_INTERFACE_DEVICE ".Gsm"
#define NM_DBUS_INTERFACE_CDMA_DEVICE       NM_DBUS_INTERFACE_DEVICE ".Cdma"
#define NM_DBUS_INTERFACE_ACTIVE_CONNECTION NM_DBUS_INTERFACE ".Connection.Active"
#define NM_DBUS_INTERFACE_IP4_CONFIG        NM_DBUS_INTERFACE ".IP4Config"


#define NM_DBUS_SERVICE_USER_SETTINGS     "org.freedesktop.NetworkManagerUserSettings"
#define NM_DBUS_SERVICE_SYSTEM_SETTINGS   "org.freedesktop.NetworkManagerSystemSettings"
#define NM_DBUS_IFACE_SETTINGS            "org.freedesktop.NetworkManagerSettings"
#define NM_DBUS_IFACE_SETTINGS_SYSTEM     "org.freedesktop.NetworkManagerSettings.System"
#define NM_DBUS_PATH_SETTINGS             "/org/freedesktop/NetworkManagerSettings"

#define NM_DBUS_IFACE_SETTINGS_CONNECTION "org.freedesktop.NetworkManagerSettings.Connection"
#define NM_DBUS_PATH_SETTINGS_CONNECTION  "/org/freedesktop/NetworkManagerSettings/Connection"
#define NM_DBUS_IFACE_SETTINGS_CONNECTION_SECRETS "org.freedesktop.NetworkManagerSettings.Connection.Secrets"


/*
 * Types of NetworkManager states
 */
typedef enum NMState
{
	NM_STATE_UNKNOWN = 0,
	NM_STATE_ASLEEP,
	NM_STATE_CONNECTING,
	NM_STATE_CONNECTED,
	NM_STATE_DISCONNECTED
} NMState;


/*
 * Types of NetworkManager devices
 */
typedef enum NMDeviceType
{
	DEVICE_TYPE_UNKNOWN = 0,
	DEVICE_TYPE_802_3_ETHERNET,
	DEVICE_TYPE_802_11_WIRELESS,
	DEVICE_TYPE_GSM,
	DEVICE_TYPE_CDMA
} NMDeviceType;


/*
 * General device capability bits
 *
 */
#define NM_DEVICE_CAP_NONE			0x00000000
#define NM_DEVICE_CAP_NM_SUPPORTED		0x00000001
#define NM_DEVICE_CAP_CARRIER_DETECT	0x00000002


/* 802.11 wireless device-specific capabilities */
#define NM_802_11_DEVICE_CAP_NONE			0x00000000
#define NM_802_11_DEVICE_CAP_CIPHER_WEP40	0x00000001
#define NM_802_11_DEVICE_CAP_CIPHER_WEP104	0x00000002
#define NM_802_11_DEVICE_CAP_CIPHER_TKIP	0x00000004
#define NM_802_11_DEVICE_CAP_CIPHER_CCMP	0x00000008
#define NM_802_11_DEVICE_CAP_WPA			0x00000010
#define NM_802_11_DEVICE_CAP_RSN			0x00000020


/*
 * 802.11 Access Point flags
 *
 */
#define NM_802_11_AP_FLAGS_NONE				0x00000000
#define NM_802_11_AP_FLAGS_PRIVACY			0x00000001

/*
 * 802.11 Access Point security flags
 *
 * These describe the current security requirements of the BSSID as extracted
 * from various pieces of beacon information, like beacon flags and various
 * information elements.
 */
#define NM_802_11_AP_SEC_NONE				0x00000000
#define NM_802_11_AP_SEC_PAIR_WEP40			0x00000001
#define NM_802_11_AP_SEC_PAIR_WEP104		0x00000002
#define NM_802_11_AP_SEC_PAIR_TKIP			0x00000004
#define NM_802_11_AP_SEC_PAIR_CCMP			0x00000008
#define NM_802_11_AP_SEC_GROUP_WEP40		0x00000010
#define NM_802_11_AP_SEC_GROUP_WEP104		0x00000020
#define NM_802_11_AP_SEC_GROUP_TKIP			0x00000040
#define NM_802_11_AP_SEC_GROUP_CCMP			0x00000080
#define NM_802_11_AP_SEC_KEY_MGMT_PSK		0x00000100
#define NM_802_11_AP_SEC_KEY_MGMT_802_1X	0x00000200

/*
 * 802.11 AP and Station modes
 *
 */
typedef enum {
	NM_802_11_MODE_UNKNOWN = 0,
	NM_802_11_MODE_ADHOC,
	NM_802_11_MODE_INFRA
} NM80211Mode;


/*
 * Device states
 */
typedef enum
{
	NM_DEVICE_STATE_UNKNOWN = 0,

	/* Initial state of all devices and the only state for devices not
	 * managed by NetworkManager.
	 *
	 * Allowed next states:
	 *   UNAVAILABLE:  the device is now managed by NetworkManager
	 */
	NM_DEVICE_STATE_UNMANAGED,

	/* Indicates the device is not yet ready for use, but is managed by
	 * NetworkManager.  For Ethernet devices, the device may not have an
	 * active carrier.  For WiFi devices, the device may not have it's radio
	 * enabled.
	 *
	 * Allowed next states:
	 *   UNMANAGED:  the device is no longer managed by NetworkManager
	 *   DISCONNECTED:  the device is now ready for use
	 */
	NM_DEVICE_STATE_UNAVAILABLE,

	/* Indicates the device does not have an activate connection to anything.
	 *
	 * Allowed next states:
	 *   UNMANAGED:  the device is no longer managed by NetworkManager
	 *   UNAVAILABLE:  the device is no longer ready for use (rfkill, no carrier, etc)
	 *   PREPARE:  the device has started activation
	 */
	NM_DEVICE_STATE_DISCONNECTED,

	/* Indicate states in device activation.
	 *
	 * Allowed next states:
	 *   UNMANAGED:  the device is no longer managed by NetworkManager
	 *   UNAVAILABLE:  the device is no longer ready for use (rfkill, no carrier, etc)
	 *   FAILED:  an error ocurred during activation
	 *   NEED_AUTH:  authentication/secrets are needed
	 *   ACTIVATED:  (IP_CONFIG only) activation was successful
	 *   DISCONNECTED:  the device's connection is no longer valid, or NetworkManager went to sleep
	 */
	NM_DEVICE_STATE_PREPARE,
	NM_DEVICE_STATE_CONFIG,
	NM_DEVICE_STATE_NEED_AUTH,
	NM_DEVICE_STATE_IP_CONFIG,

	/* Indicates the device is part of an active network connection.
	 *
	 * Allowed next states:
	 *   UNMANAGED:  the device is no longer managed by NetworkManager
	 *   UNAVAILABLE:  the device is no longer ready for use (rfkill, no carrier, etc)
	 *   FAILED:  a DHCP lease was not renewed, or another error
	 *   DISCONNECTED:  the device's connection is no longer valid, or NetworkManager went to sleep
	 */
	NM_DEVICE_STATE_ACTIVATED,

	/* Indicates the device's activation failed.
	 *
	 * Allowed next states:
	 *   UNMANAGED:  the device is no longer managed by NetworkManager
	 *   UNAVAILABLE:  the device is no longer ready for use (rfkill, no carrier, etc)
	 *   DISCONNECTED:  the device's connection is ready for activation, or NetworkManager went to sleep
	 */
	NM_DEVICE_STATE_FAILED
} NMDeviceState;


typedef enum {
	NM_ACTIVE_CONNECTION_STATE_UNKNOWN = 0,

	/* Indicates the connection is activating */
	NM_ACTIVE_CONNECTION_STATE_ACTIVATING,

	/* Indicates the connection is currently active */
	NM_ACTIVE_CONNECTION_STATE_ACTIVATED
} NMActiveConnectionState;


#endif /* NETWORK_MANAGER_H */

