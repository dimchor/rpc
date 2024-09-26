# ONC RPC assignment
This is a university assignment for a course called Distributed Systems. In the assignment ONC RPC is used to create a small application that does vector maths.

## Design
The following diagram explains the architecture of the application:

![diagram](https://github.com/user-attachments/assets/b12861f7-e57b-4df8-b50e-211248ca9875)

_Left-to-right: RPC Server ↔ RPC Client & Socket Server ↔ Socket Client_

Socket Client makes a request to Socket Server. Then, Socket Server forwards the request to RPC Client. RPC Client makes the appropriate RPC call to the RPC Server. The RPC Server processes the request and returns the result backwards.

## Dependencies
The following libraries were used:
- ONC RPC
- UNIX Sockets
- GNU Check

