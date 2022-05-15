# What is this?
It's an example API of how to write REST API in c++ using crowcpp. It's an api for anonymous blogging.
It uses redis as database example, as I found it the easiest to get going with.

# How to use
The example uses redis database, so start an instance in your local machine at port: `6379`

If you have docker you can just
```
docker run --name redis-local -p 6379:6379 -d redis
```

Now install boost on your system, you can follow [this guide](https://crowcpp.org/master/getting_started/setup/linux/)

Now you can build and run:
```
mkdir build && cd build
cmake ..
make
./cppREST
```
