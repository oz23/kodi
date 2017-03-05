#pragma once
/*
 *      Copyright (C) 2005-2017 Team Kodi
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with KODI; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "AddonBase.h"
#include "definitions.h"

//==============================================================================
///
/// \defgroup cpp_kodi_network  Interface - kodi::network
/// \ingroup cpp
/// @brief **Network functions**
///
/// The network module offers functions that allow you to control it.
///
/// These are pure static functions them no other initialization need.
///
/// It has the header \ref Network.h "#include <kodi/Network.h>" be included
/// to enjoy it.
///
//------------------------------------------------------------------------------

namespace kodi
{
namespace network
{

  //============================================================================
  ///
  /// \ingroup cpp_kodi_network
  /// @brief Send WakeOnLan magic packet.
  ///
  /// @param[in] mac Network address of the host to wake.
  /// @return True if the magic packet was successfully sent, false otherwise.
  ///
  inline bool WakeOnLan(const std::string& mac)
  {
    return ::kodi::addon::CAddonBase::m_interface->toKodi.kodi->network.wake_on_lan(::kodi::addon::CAddonBase::m_interface->toKodi.kodiBase, mac.c_str());
  }
  //----------------------------------------------------------------------------


  //============================================================================
  ///
  /// \ingroup cpp_kodi_network
  /// @brief To the current own ip address as a string.
  ///
  /// @return Own system ip.
  ///
  ///
  /// ------------------------------------------------------------------------
  ///
  /// **Example:**
  /// ~~~~~~~~~~~~~{.cpp}
  /// #include <kodi/Network.h>
  /// ...
  /// std::string strIpAddress = kodi::network::GetIPAddress();
  /// fprintf(stderr, "My IP is '%s'\n", strIpAddress.c_str());
  /// ...
  /// ~~~~~~~~~~~~~
  ///
  inline std::string GetIPAddress()
  {
    std::string ip;
    char* string = ::kodi::addon::CAddonBase::m_interface->toKodi.kodi->network.get_ip_address(::kodi::addon::CAddonBase::m_interface->toKodi.kodiBase);
    if (string != nullptr)
    {
      ip = string;
      ::kodi::addon::CAddonBase::m_interface->toKodi.free_string(::kodi::addon::CAddonBase::m_interface->toKodi.kodiBase, string);
    }
    return ip;
  }
  //----------------------------------------------------------------------------


  //============================================================================
  ///
  /// \ingroup cpp_kodi_network
  /// @brief URL encodes the given string
  ///
  /// This function converts the given input string to a URL encoded string and
  /// returns that as a new allocated string. All input characters that are
  /// not a-z, A-Z, 0-9, '-', '.', '_' or '~' are converted to their "URL escaped"
  /// version (%NN where NN is a two-digit hexadecimal number).
  ///
  /// @param[in] url The code of the message to get.
  /// @return Encoded URL string
  ///
  ///
  /// ------------------------------------------------------------------------
  ///
  /// **Example:**
  /// ~~~~~~~~~~~~~{.cpp}
  /// #include <kodi/Network.h>
  /// ...
  /// std::string encodedUrl = kodi::network::URLEncode("François");
  /// fprintf(stderr, "Encoded URL is '%s'\n", encodedUrl.c_str());
  /// ...
  /// ~~~~~~~~~~~~~
  /// For example, the string: François ,would be encoded as: Fran%C3%A7ois
  ///
  inline std::string URLEncode(const std::string& url)
  {
    std::string retString;
    char* string = ::kodi::addon::CAddonBase::m_interface->toKodi.kodi->network.url_encode(::kodi::addon::CAddonBase::m_interface->toKodi.kodiBase, url.c_str());
    if (string != nullptr)
    {
      retString = string;
      ::kodi::addon::CAddonBase::m_interface->toKodi.free_string(::kodi::addon::CAddonBase::m_interface->toKodi.kodiBase, string);
    }
    return retString;
  }
  //----------------------------------------------------------------------------


  //============================================================================
  ///
  /// \ingroup cpp_kodi_network
  /// @brief Lookup URL in DNS cache
  ///
  /// This test will get DNS record for a domain. The DNS lookup is done directly
  /// against the domain's authoritative name server, so changes to DNS Records
  /// should show up instantly. By default, the DNS lookup tool will return an
  /// IP address if you give it a name (e.g. www.example.com)
  ///
  /// @param[in] strHostName  The code of the message to get.
  /// @param[in] strIpAddress Returned address
  /// @return true if successfull
  ///
  ///
  /// ------------------------------------------------------------------------
  ///
  /// **Example:**
  /// ~~~~~~~~~~~~~{.cpp}
  /// #include <kodi/Network.h>
  /// ...
  /// std::string strIpAddress;
  /// bool ret = kodi::network::DNSLookup("www.google.com", strIpAddress);
  /// fprintf(stderr, "DNSLookup returned for www.google.com the IP '%s', call was %s\n", strIpAddress.c_str(), ret ? "ok" : "failed");
  /// ...
  /// ~~~~~~~~~~~~~
  ///
  inline bool DNSLookup(const std::string& strHostName, std::string& strIpAddress)
  {
    bool ret = false;
    char* ipAddress = ::kodi::addon::CAddonBase::m_interface->toKodi.kodi->network.dns_lookup(::kodi::addon::CAddonBase::m_interface->toKodi.kodiBase, strHostName.c_str(), &ret);
    if (ipAddress != nullptr)
    {
      strIpAddress = ipAddress;
      ::kodi::addon::CAddonBase::m_interface->toKodi.free_string(::kodi::addon::CAddonBase::m_interface->toKodi.kodiBase, ipAddress);
    }
    return ret;
  }
  //----------------------------------------------------------------------------

} /* namespace network */
} /* namespace kodi */
