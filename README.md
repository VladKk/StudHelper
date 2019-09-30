# StudHelper

Program which helps to track all the marks you'll add and give some useful information about yours academic performance.

## Getting Started

To start working with StudHelper, just install it from GitHub and unpack it.

### Prerequisites

To work with StudHelper, you need to have PostgreSQL to be installed.
For Debian:
First, you need to import PostgreSQL packages signing key on your system. Use the below command to import the key.

```
wget -q https://www.postgresql.org/media/keys/ACCC4CF8.asc -O - | sudo apt-key add -
```

Now add PostgreSQL apt repository in your system as per your operating system. These are suggested on official PostgreSQL [website](https://www.postgresql.org/download/linux/ubuntu/) using following command.

```
sudo sh -c 'echo "deb http://apt.postgresql.org/pub/repos/apt/ jessie-pgdg main" >> /etc/apt/sources.list.d/pgdg.list'

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

* [PostgreSQL](https://www.postgresql.org) - database which StudHelper was created with
* [LibXL](http://www.libxl.com) - Excel library (served as database on the early versions of StudHelper)

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

* This is my first projects and it has a lot of mistakes, so don't judge strictly)

