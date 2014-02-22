# server playground

Playing around with some code found here: http://www.cs.tau.ac.il/~eddiea/samples/Multiplexing/tcp-multiplexing-server.c

I've cleaned it up so that it compiles (sort of) in OSX. No idea if it works in other bsd/nixes.

## todo

- why is node throwing an error? shouldn't `close(..)` send a proper FIN packet?
- rework client code so it doesnt look horrible
- do something real on the server side
- accept commands from node