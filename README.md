# BookStore-gRPC
Rewrite a Rest BookStore API server in gRPC

#### Build and Run

#### Test

We use `grpcurl` to test it.

##### Create(POST) a book

```bash
user@matin ~/o/g/e/c/BookStore-gRPC (main)> grpcurl -plaintext  -d '{"name": "fitzgerald", "author": "gatsby"}'  localhost:50051 bookstore.BookStore.PostBook
{
  "msg": "Book created with id: 2106477622"
}
user@matin ~/o/g/e/c/BookStore-gRPC (main)> 
```



##### Get the list of all books

```bash
user@matin ~/o/g/e/c/BookStore-gRPC (main)> grpcurl -plaintext localhost:50051 bookstore.BookStore.GetAllBooks
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
{
  "id": 1650682338,
  "name": "fitzgerald",
  "author": "gatsby"
}
{
  "id": 2106477622,
  "name": "fitzgerald",
  "author": "gatsby"
}
user@matin ~/o/g/e/c/BookStore-gRPC (main)> 
```

##### Get a book

```bash
user@matin ~/o/g/e/c/BookStore-gRPC (main)> grpcurl -plaintext -d '{"id": 1029625494}' localhost:50051 bookstore.BookStore.GetABookById
{
  "id": 1029625494,
  "name": "fitzgerald",
  "author": "gatsbees"
}
user@matin ~/o/g/e/c/BookStore-gRPC (main)> 
```



##### Delete a book

```bash
user@matin ~/o/g/e/c/BookStore-gRPC (main)> grpcurl -plaintext -d '{"id": 877404536}' localhost:50051 bookstore.BookStore.DeleteABook
ERROR:
  Code: NotFound
  Message: No book entry found for this id
user@matin ~/o/g/e/c/BookStore-gRPC (main) [69]>
user@matin ~/o/g/e/c/BookStore-gRPC (main) [69]> grpcurl -plaintext -d '{"id": 94352545}' localhost:50051 bookstore.BookStore.DeleteABook
{
  
}
user@matin ~/o/g/e/c/BookStore-gRPC (main)> 
```

##### Update a Book

```bash
user@matin ~/o/g/e/c/BookStore-gRPC (main)> grpcurl -plaintext  -d '{"id": 877404536, "name": "fitzgerald", "author": "gatsbees"}'  localhost:50051 bookstore.BookStore.UpdateABook
ERROR:
  Code: NotFound
  Message: No book entry found for this id
user@matin ~/o/g/e/c/BookStore-gRPC (main) [69]>
user@matin ~/o/g/e/c/BookStore-gRPC (main)> grpcurl -plaintext  -d '{"id": 1029625494, "name": "fitzgerald", "author": "gatsbees"}'  localhost:50051 bookstore.BookStore.UpdateABook

{
  "id": 1029625494,
  "name": "fitzgerald",
  "author": "gatsbees"
}
user@matin ~/o/g/e/c/BookStore-gRPC (main)> 

```

