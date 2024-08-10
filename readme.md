## Fadhil's telegram bot
personal assistant telegram bot

## Dependencies 
- [TgBot](https://github.com/reo7sp/tgbot-cpp)
- Boost
- OpenSSL
- [fmt](https://github.com/fmtlib/fmt)
- Zlib
- cURL
- [log.c](https://github.com/fadhil-riyanto/log.c-patched) (submodule)
- [inih](https://github.com/benhoyt/inih) (submodule)
- [googletest](https://github.com/google/googletest) (test)

## build instructions
currenly, supported platform only linux. I have no plans to make a windows version.

make sure all dependencies are installed, and you need <b>several GB</b> of ram.

### 1. Install dependencies

pacman
```
sudo pacman -Syu
sudo pacman -S cmake boost openssl zlib curl fmt
```

optional (testing)
```
sudo pacman -S gtest
```

### 2. build tgbot-cpp from source
```
git clone https://github.com/fadhil-riyanto/tgbot-cpp
cd tgbot-cpp
cmake .
make -j4
sudo make install
```

### 3. build the bot

```
git clone https://github.com/fadhil-riyanto/fadhil-riyanto-bot.git

cd fadhil-riyanto-bot
git submodule update --init --recursive --depth 1
make all_libs -j4 && make all -j4
```


## Licence
license: [GPL-3.0](https://github.com/fadhil-riyanto/fadhil-riyanto-bot/blob/master/license)