# tcp_tee
A netwrork utility to forward and dump tcp port data.

Connection before:
```
client <-------> server
```
Connection with tcp_tee:
```
client  <--- tcp_tee ---> server
              |
              v
              ./request.log
              ./responce.log
```
Tcp_tee utility listens some tcp port (8080 by default) and forwards all data to some server (127.0.0.1:80 by default). All transferred data being dump into .log files.
