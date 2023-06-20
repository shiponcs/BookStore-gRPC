# BookStore-gRPC
A BookStore API server in written in gRPC

#### Build using Cmake

After cloning the repo, from root directory of it run: 

```bash
$ mkdir -p build
$ cd build
$ cmake ..
$ make
# run
$ ./server
```

#### Use Docker Image

```bash
$ docker pull ghcr.io/shiponcs/bookstore-grpc:1.0
$ docker run -p 50051:50051 ghcr.io/shiponcs/bookstore-grpc:1.0
```





#### Test

We use `grpcurl` to test it.

##### Create(POST) a book

```bash
$ grpcurl -plaintext  -d '{"name": "fitzgerald", "author": "gatsby"}'  localhost:50051 bookstore.BookStore.PostBook
{
  "msg": "Book created with id: 2106477622"
}
$ 
```



##### Get the list of all books

```bash
$ grpcurl -plaintext localhost:50051 bookstore.BookStore.GetAllBooks
{
  "id": 94352545,
  "name": "fitzgerald",
  "author": "gatsby"
}
{
  "id": 1029625494,
  "name": "fitzgerald",
  "author": "gatsby"
}
{
  "id": 1495894131,
  "name": "fitzgerald",
  "author": "gatsby"
}
$ 
```

##### Get a book

```bash
$ grpcurl -plaintext -d '{"id": 1029625494}' localhost:50051 bookstore.BookStore.GetABookById
{
  "id": 1029625494,
  "name": "fitzgerald",
  "author": "gatsbees"
}
$ 
```



##### Delete a book

```bash
$ grpcurl -plaintext -d '{"id": 877404536}' localhost:50051 bookstore.BookStore.DeleteABook
ERROR:
  Code: NotFound
  Message: No book entry found for this id
user@matin ~/o/g/e/c/BookStore-gRPC (main) [69]>
user@matin ~/o/g/e/c/BookStore-gRPC (main) [69]> grpcurl -plaintext -d '{"id": 94352545}' localhost:50051 bookstore.BookStore.DeleteABook
{
  
}
$ 
```

##### Update a Book

```bash
$ grpcurl -plaintext  -d '{"id": 877404536, "name": "fitzgerald", "author": "gatsbees"}'  localhost:50051 bookstore.BookStore.UpdateABook
ERROR:
  Code: NotFound
  Message: No book entry found for this id
user@matin ~/o/g/e/c/BookStore-gRPC (main) [69]>
$ grpcurl -plaintext  -d '{"id": 1029625494, "name": "fitzgerald", "author": "gatsbees"}'  localhost:50051 bookstore.BookStore.UpdateABook

{
  "id": 1029625494,
  "name": "fitzgerald",
  "author": "gatsbees"
}
$ 

```

