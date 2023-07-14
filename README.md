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
Tcp_tee utility listens on some tcp port (8080 by default) and forwards all data to a server you want (127.0.0.1:80 by default). Tcp_tee saves all transmitted data to .log files.

It is usefull to quickly monitor http traffic or other tcp traffic. It is a simplified tcpdump alternative wich is compatible with most OSes.
```
Usage:
tcp_tee [--listen_port 8080] [--forward_address 127.0.0.1] [--forward_port 80] [--request_log_file request.log ] [--responce_log_file responce.log]
```

```
Usage example:

$tcp_tee --listen_port 8080 --forward_address some-site.com --forward_port 80  &     #run tcp_tee in background
$curl http://127.0.0.1:8080/index.html                                               #get http://some-site.com/index.html 
$cat request.log                                                                     #show request
$cat responce.log                                                                    #show responce
```



# Build from source

run build.sh
or run the following commands:
```
mkdir build
cd build
conan install ..
#conan install --build missing .. 
cmake .. 
cmake --build . 
```

If you face strange linkage errors then check if conan package manager is configured to use c++11 ABI. You should get the following output:
```
$ grep compiler.libcxx ~/.conan/profiles/default
compiler.libcxx=libstdc++11
```

# Compatibility

Checked on
- Ubuntu 22, gcc 11.3
- Windows 10, MSVS 2022

# Licence

You are free to use or modify this code.
