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
- [pugixml](https://github.com/zeux/pugixml) (submodule, checkout tags newest please)
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

### 3. build telegram-bot-api server
this server make your bot fast than default api.telegram.org

```
git clone --recursive https://github.com/tdlib/telegram-bot-api.git
cd telegram-bot-api
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --target install
```

start the service, you need api_id and api_hash from https://my.telegram.org/

```
telegram-bot-api --api-id=YOUR_API_ID --api-hash=YOUR_API_HASH --local --http-ip-address=127.0.0.1
```

### 4. build the bot

```
git clone https://github.com/fadhil-riyanto/fadhil-riyanto-bot.git

cd fadhil-riyanto-bot
git submodule update
mkdir build
cmake ..
make -j4
```

### 4. build server mode
This will use api.telegram.org instead selfhosted server, you can skip step 3

add `add_compile_definitions("-DSERVER_ENV")` to the CMakeLists.txt

## Licence
license: [GPL-3.0](https://github.com/fadhil-riyanto/fadhil-riyanto-bot/blob/master/license)


## Maintainer
Fadhil Riyanto <me@fadev.org>