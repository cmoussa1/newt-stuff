## Node Genders

_genders: node key-value pair database that sysadmins use for cluster configuration_

Genders are used with a tool called `nodeattr` to check those attributes:

```
[moussa1@machine160:~]$ nodeattr mgmt; echo $?

[moussa1@machine160:~]$ nodeattr login; echo $?
```

By default, when you run a query, `nodeattr` checks "do I ('I' being the node I'm on) have this attribute?" Then the exit code can be used for scripting. On the above example, you can script to see if you are currently on a management node or a login node.

```
[moussa1@machine:~]$ nodeattr mgmt ; echo $?
1
[moussa1@machine:~]$ nodeattr login ; echo $?
0
```

so a series of `if` statements in scripts could be like:

```
if nodeattr mgmt;
then run_mgmt_setup_script.sh;
fi
```

There are also ways to query for values of keys, which would also be used in scripting

```
[moussa1@machine160:~]$ nodeattr -v ldmsd_xprt
rdma
```

In several projects, they are used for gathering the "master list" of nodes in the cluster, because ultimately that's something a number of tools require.

`nodeattr -A` gives you the nodes in the cluster

`pdsh` can use genders too:

`pdsh -g mgmt hostname`

`pdsh -g login hostname`

`pdsh -g gw hostname`

So instead of specifying the nodes themselves (if we don't know the specific nodes), we can just specify the type of node to run the command on.

Generally speaking, genders is only nodes, attributes, and values. It has no knowledge of meaning of anything that's entered. Only minor formatting (i.e. legal hostnames) and stuff like that are checked.


##### cluster layout

There are mgmt nodes, only sysadmins and appropriate staff can get to them, running critical cluster daemons.

Login nodes are for users to login, compile, and launch jobs.

Gateway nodes are for routing traffic.

Compute nodes are for running jobs; only users running on those nodes can login to them.

Smaller clusters have a single mgmt node, bigger ones have two.
- the naming convention for mgmt nodes are the "i" and "j" consolidates
- there are primary mgmt nodes and alternate mgmt nodes

Every node in a cluster typically has multiple network connections, minimally one high speed connection and one ethernet connection. The ethernet connection is for management purposes, monitoring, SLURM communication, etc. The high speed one is for Lustre and user MPI traffic.

`pdsh` has smarts with genders to run over the management network when you `pdsh` to nodes.

Gateway nodes serve as the magic to get data from the compute cluster to the storage servers. Those GW nodes have their own connection to a storage server that compute nodes don't have a connection to.
