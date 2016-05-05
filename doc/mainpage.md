Introduction {#mainpage}
============

[Cynara](https://wiki.tizen.org/wiki/Security:Cynara) is fast, simple and safe policy-checker
service.

Functions of Cynara are:
* checking access for certain privileges
* holding policies
* simple, single function API - for checking policies
* thin client library - to make access control even more simple
* ability to use external agent (in case of policies that can't be fully processed in Cynara and
  plugins)


# API
Cynara's API is split into two parts:
* client API for privilege checking API - easily accessed with libCynara by anyone
* admin API for policy managing API - accessed only by trusted processes with libCynaraAdmin.

Cynara service uses separate Unix Domain Sockets for handling each type of API.


## Client
Both synchronous and asynchronous client API for Cynara are available. They are provided by
libcynara-client and libcynara-client-async libraries.

[Details of client synchronous API](@ref cynara-client.h)

[Details of client asynchronous API](@ref cynara-client-async.h)

To enhance client performance a simple LRU Cache was implemented for both synchronous and
asynchronous client API. Cache is available in Cynara since version 0.2.0.

[Details of cache](https://wiki.tizen.org/wiki/Security:Cynara:API:client-cache)

Application context is built of: application identifier and user identifier that thanks to great
flexibility can be defined according to requirements of each individual distribution or
administrator. Tizen 3.0 was the first distribution to use Cynara and it has choosen to use Smack
label for application identification and string coded UID for user recognition.

There might be a problem, if IPC between application and service do not provide credentials of an
application. The only way to obtain application context is probably reading it from /proc/PID
(service needs RX to application Smack label for that).

Direct ways of getting these information is described on [wiki][1], but users are strongly
recommended to use credential helpers libraries.

[1]: https://wiki.tizen.org/wiki/Security:Cynara:ApplicationCredentials


## Admin
Admin API is the only way to change policy kept in Cynara. Its usage needs root privileges. This
restriction guarantees that no unprivileged process can alter Cynara's policy.

[Details of admin API](@ref cynara-admin.h)

### Tizen
In Tizen 3.0, there is a dedicated service -- Security Manager -- to make changes to Cynara's policy
and should probably be the only user of Cynara's admin interface. Processes that would like to
change Cynara's policy (e.g. installers) should use libsecurity-manager-client library instead of
directly invoking Cynara's admin API.

## Plugins
### Description
Plugin API enables creating independent plugins for Cynara extensions. Plugins are shared libraries
dynamically loaded into Cynara. They provide entry points defined by API to create external plugin
entities. Plugin API is based on class interfaces, which define methods needed for both client-
and service-side plugins.


### Client plugin
Client plugins are responsible for interpreting external policy types, which can be delivered
to client as Cynara response, and translate them to [CYNARA_API_ACCESS_ALLOWED][2] or
[CYNARA_API_ACCESS_DENIED][3]. Plugins are only allowed to interpret policy types declared by
overridden [4] method. Client plugins usually come together with service plugin (for e.g. askuser
agent – available in tizen.org [repository][5] or [GitHub][6]).

[2]: @ref CYNARA_API_ACCESS_ALLOWED
[3]: @ref CYNARA_API_ACCESS_DENIED


### Service plugin
Service plugins are responsible for interpreting external policy types. Communication with Cynara's
agent extensions could be required for this to work. Plugins are only allowed to interpret policy
types declared by overridden [4] method. Service plugins usually come together with Cynara agent
extension (for e.g. askuser agent – available in tizen.org [repository][5] or [GitHub][6]).

[Details of plugin API](@ref cynara-plugin.h)

[4]: @ref Cynara::ExternalPluginInterface::getSupportedPolicyDescr "getSupportedPolicyDescr()"
[5]: https://review.tizen.org/gerrit/#/admin/projects/platform/core/security/askuser
[6]: https://github.com/samsung/askuser


## Protocols
[Description of protocol for communication with cynara][7]
[7]: https://wiki.tizen.org/wiki/Security:Cynara:Protocols


## Credentials
The helper APIs can be used to create:
* client identification strings
* user identification strings

Identification strings are necessary to specify Cynara policies. However, it is important to notice
that usage of strings generated by these helper APIs is not obligatory – a different consistent way
of client and user process identification strings might be introduced.

The client identification string might be generated based on the client process PID or Smack label.
The user identification string might be generated based on the client process UID (user id) or
Smack label. The default methods for a system might be obtained by calling
cynara_creds_get_default_client_method or cynara_creds_get_default_user_method respectively.

Currently, there are two sets of functions which generate the identification strings.
The one is based on DBUS connection, the other is based on Unix socket file descriptors.
The connections and socket descriptors are used to obtain the PID, Smack or UID associated
with the client or user process.

In addition to the functions generating the identification strings, there are functions returning
the PID of the process on the other side of socket/dbus connection. The PID might be used to
generate different identification strings.

Details of credentials helper libraries:
[commons](@ref cynara-creds-commons.h),
[dbus](@ref cynara-creds-dbus.h),
[gdbus](@ref cynara-creds-gdbus.h),
[socket](@ref cynara-creds-socket.h).


## Session
This helper API can be used to create a client session string identifiers based on PID and time of
creation a client process. Session string identifiers are used in in cynara_check() and
cynara_async_create_request() functions defined in client libraries. It is important to notice that
usage of strings generated by session library APIs is not obligatory – a different consistent way
of identifiers generation might be introduced.

[Details of session helper library](@ref cynara-session.h)


## Agent
Cynara plugins may use external applications (agents) in order to perform some action on privilege
check request. [Agent API](@ref cynara-agent.h) allows communication between plugins and agents.