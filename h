[1mdiff --git a/api/index.js b/api/index.js[m
[1mindex be8c108..00d232b 100644[m
[1m--- a/api/index.js[m
[1m+++ b/api/index.js[m
[36m@@ -140,10 +140,10 @@[m [mapp.get('/admin/:command', function(req,res) {[m
        case "clear":[m
          if (req.query.db == "mongo") {[m
            msg = "clearing mongo";[m
[31m-           /* UNIMPLEMENTED */[m
[32m+[m[32m           db.public.many("cls")[m
 	 } else if (req.query.db == "psql") {[m
            msg = "clearing psql";[m
[31m-           /* UNIMPLEMENTED */[m
[32m+[m[32m           db.public.many("DBCC DROPCLEANBUFFERS")[m
 	 } else {[m
            msg = "unknown db " + req.query.db;[m
          }[m
[36m@@ -151,10 +151,11 @@[m [mapp.get('/admin/:command', function(req,res) {[m
        case "save":[m
          if (req.query.db == "mongo") {[m
            msg = "saving mongo to " + req.query.file;[m
[31m-           /* UNIMPLEMENTED */[m
[32m+[m[32m           db.public.save(req.query.file)[m
[32m+[m[41m           [m
 	 } else if (req.query.db == "psql") {[m
            msg = "saving psql " + req.query.file;[m
[31m-           /* UNIMPLEMENTED */[m
[32m+[m[32m           db.public.save(req.query.file)[m
 	 } else {[m
            msg = "unknown db " + req.query.db;[m
          }[m
[36m@@ -180,20 +181,31 @@[m [mapp.get('/admin/:command', function(req,res) {[m
 startDatabase().then(async() => {[m
     await insertMeasurement({id:'00', t:'18', h:'78'});[m
     await insertMeasurement({id:'00', t:'19', h:'77'});[m
[31m-    await insertMeasurement({id:'00', t:'17', h:'77'});[m
[32m+[m[32m    await insertMeasurement({id:'00', t:'40', h:'77'});[m
     await insertMeasurement({id:'01', t:'17', h:'77'});[m
     console.log("mongo measurement database Up");[m
 [m
     db.public.none("CREATE TABLE devices (device_id VARCHAR, name VARCHAR, key VARCHAR)");[m
[31m-    db.public.none("INSERT INTO devices VALUES ('00', 'Fake Device 00', '123456')");[m
[31m-    db.public.none("INSERT INTO devices VALUES ('01', 'Fake Device 01', '234567')");[m
[32m+[m[32m    db.public.none("INSERT INTO devices VALUES ('00', 'Example Device 00', '123456')");[m
[32m+[m[32m    db.public.none("INSERT INTO devices VALUES ('01', 'Example Device 01', '234567')");[m
     db.public.none("CREATE TABLE users (user_id VARCHAR, name VARCHAR, key VARCHAR)");[m
     db.public.none("INSERT INTO users VALUES ('1','Ana','admin123')");[m
     db.public.none("INSERT INTO users VALUES ('2','Beto','user123')");[m
 [m
     console.log("sql device database up");[m
[32m+[m[32m    let date = new Date()[m
 [m
[32m+[m[32m    let day = date.getDate()[m
[32m+[m[32m    let month = date.getMonth() + 1[m
[32m+[m[32m    let year = date.getFullYear()[m
[32m+[m
[32m+[m[41m    [m
     app.listen(PORT, () => {[m
[32m+[m[32m        if(month < 10){[m
[32m+[m[32m            console.log(`${day}-0${month}-${year}`)[m
[32m+[m[32m        }else{[m
[32m+[m[32m            console.log(`${day}-${month}-${year}`)[m
[32m+[m[32m        }[m
         console.log(`Listening at ${PORT}`);[m
     });[m
 });[m
[1mdiff --git a/perception/config/config.h.template b/perception/config/config.h.template[m
[1mindex 50021eb..088f726 100644[m
[1m--- a/perception/config/config.h.template[m
[1m+++ b/perception/config/config.h.template[m
[36m@@ -4,10 +4,10 @@[m
 #define API_PORT      "8080"[m
 #define API_IP_PORT   API_IP ":" API_PORT[m
 [m
[31m-#define WIFI_SSID     ""[m
[31m-#define WIFI_PASSWORD ""[m
[32m+[m[32m#define WIFI_SSID     "Telecentro-e0a0"[m
[32m+[m[32m#define WIFI_PASSWORD "ZJMYQ2YZET5G"[m
 [m
[31m-#define DEVICE_ID     ""[m
[32m+[m[32m#define DEVICE_ID     "jc:Xn:ni:38"[m
 [m
 [m
 // esp32-dht11 [m
[36m@@ -22,9 +22,9 @@[m
 // #define ONE_WIRE_GPIO 2[m
 [m
 // esp32c3-bmp280 [m
[31m-// #define SDA_GPIO      4[m
[31m-// #define SCL_GPIO      5[m
[31m-// #define USER_AGENT    "esp-idf/1.0 esp32c3"[m
[32m+[m[32m#define SDA_GPIO      4[m
[32m+[m[32m#define SCL_GPIO      5[m
[32m+[m[32m#define USER_AGENT    "esp-idf/1.0 esp32c3"[m
 [m
 // esp32-bmp280 [m
 // #define SDA_GPIO     21[m
[1mdiff --git a/tools/post_device.sh b/tools/post_device.sh[m
[1mindex 232cfa2..c3ef597 100755[m
[1m--- a/tools/post_device.sh[m
[1m+++ b/tools/post_device.sh[m
[36m@@ -1 +1,3 @@[m
[31m-wget -O - --method=POST http://localhost:8080/device --body-data="id=$1&n=$2&k=$3"[m
[32m+[m[32mkey=$((RANDOM%99999999+10000000))[m
[32m+[m
[32m+[m[32mwget -O - --method=POST http://localhost:8080/device --body-data="id=${id}&n=$2&k=${key}"[m
[1mdiff --git a/tools/post_measurement.sh b/tools/post_measurement.sh[m
[1mindex 83f753e..211ad0d 100755[m
[1m--- a/tools/post_measurement.sh[m
[1m+++ b/tools/post_measurement.sh[m
[36m@@ -1 +1 @@[m
[31m-wget -O - --method=POST http://localhost:8080/measurement --body-data="id=$1&t=$2&h=$3"[m
[32m+[m[32mwget -O - --method=POST http://localhost:8080/measurement --body-data="id=$1&t=$2&h=$3&p=$4"[m
