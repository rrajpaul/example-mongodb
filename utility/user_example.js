const MongoClient = require('mongodb').MongoClient;

const url = 'mongodb://localhost:27017';
const db_name = "oatpp_example";
const coll_name = "user_example";

MongoClient.connect(url, { useNewUrlParser: true }, function(err, db) {
  if (err) throw err;
  var dbo = db.db(db_name);
  var myobj = {
    "id": 2,
    "first-name":
    "Janet",
    "last-name": "Doe",
    "friends": [
      "Jack Smith",
      "Neo"
    ]
  };
  dbo.collection(coll_name).insertOne(myobj, function(err, res) {
    if (err) throw err;
    console.log("1 document inserted");
  });

  myobj = {
    "id" : 1,
    "first-name" : "John",
    "last-name" : "Doe",
    "friends" : [
      "Mary Jane",
      "Peter Parker"
    ]
  };
  dbo.collection(coll_name).insertOne(myobj, function(err, res) {
    if (err) throw err;
    console.log("1 document inserted");
  });
  db.close();
});
