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
Tcp_tee utility listens on some tcp port (8080 by default) and forwards all data to some server (127.0.0.1:80 by default). Tcp_tee saves all tranmitted data to .log files.

It is usefull to quickly monitor http traffic.
```
Usage:
tcp_tee [-l |--listen_port 8080] [-a|--forward_address 127.0.0.1] [-p | --forward_port 80] [-L|--request_log_file request.log ] [-O|--responce_log_file responce.log]
```
