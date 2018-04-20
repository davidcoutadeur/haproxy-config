haproxy configuration with OpenLDAP
================================================================================

Abstract
--------

The goal is to have a failover system with OpenLDAP.
The system must switch if
- one of the service stops
- one of the service does not answer (parameters to define)


Installation
------------

yum install haproxy
mv /etc/haproxy/haproxy.{cfg,cfg.old}
```

Use the haproxy.cfg file provided, to copy in /etc/haproxy

Adapt :
- IPs referencing OpenLDAP services,
- listening port of OpenLDAP, both in OpenLDAP and haproxy configuration

Start OpenLDAP and haproxy

Check that everything is ok on the statistics interface of both servers:
```
http://<IP_SERVEUR>:8080/haproxy?stats
```

Stopping of OpenLDAP service on one node will trigger trafic redirection on
the other node.

The uncommented configuration makes a basic TCP check, which is very efficient,
but does not guarantee that the directory has a working database backend.
(corruption of data for example, which is quite rare now)

There is an alternative check that sends a binary request, and wait for a
correct bind response.
The generateBind program is used to generate this bind request by
giving it the account (bindDN) and the corresponding password (bindPW).


Documentation
-------------

See the configuration file `haproxy.cfg`, describing all the useful parameters.


