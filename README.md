# FSMBOT

## An attempt to apply с++20 coroutines in practice. Used them as FSM for user registration and subsequent data updates. Some parts, such as input validation, are left without concrete implementation, since, again, the main thing is to integrate coroutines into the project. For the same reasons, there is no logging and webhook

## Key features
### To work with the bot, the user must go through the registration procedure. After that, he can view his data and update some information. This is where the functionality ends.

## Run locally
```
mkdir build && cd build
cmake ..
make 
./fsm
```