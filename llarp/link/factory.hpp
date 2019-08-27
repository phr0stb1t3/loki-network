#ifndef LLARP_LINK_FACTORY_HPP
#define LLARP_LINK_FACTORY_HPP
#include <util/string_view.hpp>
#include <functional>

#include <link/server.hpp>

namespace llarp
{
  /// LinkFactory is responsible for returning std::functions that create the
  /// link layer types
  struct LinkFactory
  {
    enum class LinkType
    {
      eLinkUTP,
      eLinkIWP,
      eLinkMempipe,
      eLinkUnknown
    };

    using Factory = std::function< LinkLayer_ptr(
        const SecretKey&, GetRCFunc, LinkMessageHandler, SignBufferFunc,
        SessionEstablishedHandler, SessionRenegotiateHandler, TimeoutHandler,
        SessionClosedHandler) >;

    /// get link type by name string
    /// if invalid returns eLinkUnspec
    static LinkType
    TypeFromName(string_view name);

    /// turns a link type into a string representation
    static std::string
    NameFromType(LinkType t);

    /// obtain a link factory of a certain type
    static Factory
    Obtain(LinkType t, bool permitInbound);
  };

}  // namespace llarp

#endif