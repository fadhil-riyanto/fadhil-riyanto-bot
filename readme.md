## Fadhil's telegram bot
personal assistant telegram bot

## Dependencies 
- [TgBot](https://github.com/reo7sp/tgbot-cpp)
- Boost
- OpenSSL
- [fmt](https://github.com/fmtlib/fmt)
- Zlib
- CUrl
- [log.c](https://github.com/fadhil-riyanto/log.c-patched) (submodule)
- [inih](https://github.com/benhoyt/inih) (submodule)
- [googletest](https://github.com/google/googletest) (test)

## build instructions
currenly, supported platform only linux. I have no plans to make a windows version.

make sure all dependencies are installed, and you need several GB of ram.

1. ```git clone https://github.com/fadhil-riyanto/fadhil-riyanto-bot.git```

2. ```cd fadhil-riyanto-bot```
2. ```git submodule update --init --recursive --depth 1```
3. ```make all_libs -j{nproc} && make all -j{nproc}``` where nproc is your cpu core


## Licence
license: [GPL-3.0](https://github.com/fadhil-riyanto/fadhil-riyanto-bot/blob/master/license)