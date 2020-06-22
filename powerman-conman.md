## powerman

_power on/off nodes. provides power management in a data center or compute cluster environment. it performs operations such as power on, power off, and power cycle via remote power controller devices._

`pm -q` will give the status of nodes on a clusters

```
[moussa1@cluster:~]$ pm -q
on:      cluster[63-180,182-184,186-192]
off:     
unknown: cluster[1-62,181]
```

`pm --off node[n]` will power off a node

```
[moussa1@cluster:~]$ pm -q
on:      opal[63-172,174-180,182-184,186-192]
off:     node[n]
unknown: cluster[1-62,181]
```

To turn it back on with debug data, pass the `-T` flag:

```
$ pm --off opal173
Command completed successfully
$ pm -T --on opal173
send(ipmi2): 'on popal173\n'
recv(ipmi2): 'popal173: ok\nipmipower> '
Command completed successfully
```

The `p` hostnames are the power IP addresses. They are mostly hidden away from users, being done behind the scenes. "on popal173" is the command being sent to the underlying power control tool, which is "ipmpipower"

powerman hides various power control tools/mechanisms, so that sysadmins don't have to bother. on every cluster, you can just type powerman commands.


## conman

_conman is a program for connecting to remote consoles being managed by `conmand`. it supports three modes of console access: monitor (read-only), interactive (read-write), and broadcast (write-only)._

To get out of the login prompt, pass `&.`
