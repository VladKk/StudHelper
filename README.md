# StudHelper

Program which helps you to track all the marks you'll add and give some useful information about yours academic performance.

### Prerequisites

To work with StudHelper, you need to have PostgreSQL to be installed.

##### For Debian:

First, you need to import PostgreSQL packages signing key on your system. Use the below command to import the key.

```
wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | sudo apt-key add -
sudo apt-get update
```

Now add PostgreSQL apt repository in your system as per your operating system. These are suggested on official PostgreSQL [website](https://www.postgresql.org/download/linux/debian/) using following command.

```
deb http://apt.postgresql.org/pub/repos/apt/ YOUR_DEBIAN_VERSION_HERE-pgdg main
```

### Connecting to PostgreSQL

After installing the PostgreSQL database server by default, it creates a user ‘postgres’ with role ‘postgres’. It also creates a system account with the same name ‘postgres’. So to connect to postgres server, login to your system as user postgres and connect database.

```
sudo su - postgres
psql
```

Now you are logged in to PostgreSQL database server. To check login info use following command from database command prompt.

```
postgres-# \conninfo
```

To disconnect from PostgreSQL database command prompt just type below command and press enter. It will return you back to Debian command prompt.

```
postgres-# \q
```

Your PostgreSQL installation has been completed successfully.

## Built With

* [LibXL](http://www.libxl.com) - Excel library (served as a tool for working with MS Excel files on the early versions of StudHelper)
* [PostgreSQL](https://www.postgresql.org) - database which StudHelper was created with
* [SFML](https://www.sfml-dev.org) - some little features (checking if port is open etc)

## Contributing

If you have suggestions, write: 
* GMail: **mrvlad008@gmail.com**
* Telegram: **@vlad_is_real** 
* Instagram: **@ncks_gwc**

## Versioning

For the versions available, see the [StudHelper](https://github.com/VladKk/StudHelper). 

## Authors

* **Vladislav Koliadenko** - *Main developer* - [VladKk](https://github.com/VladKk)

## Acknowledgments

* This is my first project and it has a lot of mistakes, so don't judge strictly:)
* The program was developed and tested on Debian and I don't know how it works on other systems

