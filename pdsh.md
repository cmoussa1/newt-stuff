## pdsh

_parallel distributed shell - runs some shell command on multiple nodes at the same time in parallel._

```
pdsh -w “machine[70-80]” hostname

machine75: machine75
machine78: machine78
machine73: machine73
machine71: machine71
machine70: machine70
machine74: machine74
machine76: machine76
machine72: machine72
machine80: machine80
machine77: machine77
machine79: machine79
```

`pdsh -A` for all nodes will probably fail because it’s nearly impossible for all nodes to be up. At least one will be down all the time
there’s a tool called `whatsup`, which shows what nodes are currently alive. We can link `whatsup` with `pdsh` by passing in the `-v` option.

Internally, `pdsh` uses a “remote shell” mechanism. we default to using `mrsh`, which is a MUNGE authenticated remote command. `pdsh` uses the `mrsh` protocol, but it doesn’t call it directly. But for `ssh`, it may call the `ssh` command directly. There are multiple different “remote shell” mechanisms in `pdsh`.

`pdsh` also has a “fanout,” the max number of shells it can do in parallel. The default is around 32, so it generally isn’t something to bother to think about unless you are suddenly debugging on a huge 1000+ node cluster.

A classic example of `pdsh` is the following:

`pdsh -w “machine[70-80]” cat ~/foo.sh` will output the contents of the file from those 11 nodes. If the contents of the file are long, at some point it runs off the screen and it’s not so convenient, so `pdsh` comes with a tool called `dshbak`, which can consolidate output.

`pdsh -w “machine[70-80]” cat hello.txt | dshbak -c` consolidates common output to “sections” on the screen, only utilizing a little bit of screen space.

`pdcp` will copy data from 1 node to all of the other nodes you specify.

`rpdcp` will copy the same file from all nodes to your current node; it is useful for gathering data or debug info.

`pdcp -w “machine[70-80]” ~moussa1/foo.txt /tmp/moussa1/foo.txt`

`rpdcp -w “machine[70-80]” /tmp/moussa1/foo.txt /tmp/moussa1` will copy all of the data from **foo.txt** on nodes `machine[70-80]` and put it into `/tmp/moussa1`.
