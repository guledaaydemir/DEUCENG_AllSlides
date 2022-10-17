
CREATE TABLE tbl_AIRPLANE
(
  "Reg_No" serial NOT NULL, -- otomatik artar -- PK
  "Name" character varying(100),
  "Model_No" character varying(100) NOT NULL, --FK 
  CONSTRAINT "PK_Reg_No" PRIMARY KEY ("Reg_No"),
  CONSTRAINT "Unique_Name" UNIQUE ("Name"),
  CONSTRAINT "FK_Model_No" FOREIGN KEY ("Model_No")
      REFERENCES tbl_MODEL ("Model_No") MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE tbl_MODEL
(
  "Model_No" character varying(100) NOT NULL, -- PK
  "Capacity" character varying(100),
  "Weight" character varying(100), 
  CONSTRAINT "PK_Model_No" PRIMARY KEY ("Model_No")
);

CREATE TABLE tbl_WORKERS
(
  "SSN" character varying(100) NOT NULL,  -- PK
  "Name" character varying(100),
  "Surname" character varying(100), 
  "Salary" character varying(100),
  CONSTRAINT "PK_SSN" PRIMARY KEY ("SSN")
);
CREATE TABLE tbl_UNION
(
  "Union_id" serial NOT NULL, -- otomatik artar -- PK
  "Name" character varying(100),
  CONSTRAINT "PK_Union_id" PRIMARY KEY ("Union_id")
  
);
CREATE TABLE tbl_TEL_NO
(
  "Tel_id"  serial NOT NULL,-- PK
  "Tel_No" character varying(12) NOT NULL, 
  "Tel_Type" character varying(100),
  CONSTRAINT "PK_Tel_id" PRIMARY KEY ("Tel_id")
  
);

CREATE TABLE tbl_ADDRESS
(
  "Address_id"  serial NOT NULL,-- PK
  "Street" character varying(100) NOT NULL, 
  "Apart_No" character varying(100),
  "District" character varying(100),
  "City" character varying(100),
  "Country" character varying(100),
  CONSTRAINT "PK_Address_id" PRIMARY KEY ("Address_id")
  
);
CREATE TABLE tbl_FAA_TEST
(
  "FAA_id"  serial NOT NULL,-- PK
  "Plane_Part" character varying(100),
  "FAA_Type" character varying(100),
  "Plane_Score" integer NOT NULL,
  "Hour_Spend" character varying(100),
  "FAA_Date" date,
  "Reg_No" integer NOT NULL,
  "FAA_Val_Period" date , 
  CONSTRAINT "PK_FAA_id" PRIMARY KEY ("FAA_id"),
  CONSTRAINT "FK_Reg_No" FOREIGN KEY ("Reg_No")
      REFERENCES tbl_AIRPLANE ("Reg_No") MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE tbl_MAINTENANCE
(
  "Main_id"  serial NOT NULL,-- PK
  "Main_Type" character varying(100), 
  "Broken_Part" character varying(100),
  "Broken_Reason" character varying(100),
  "Reg_No" integer NOT NULL,
  "Main_Period" date,
  "FAA_id"  integer NOT NULL,
  CONSTRAINT "PK_Main_id" PRIMARY KEY ("Main_id"),
  CONSTRAINT "FK_Reg_No" FOREIGN KEY ("Reg_No")
      REFERENCES tbl_AIRPLANE ("Reg_No") MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE,
  CONSTRAINT "FK_FAA_id" FOREIGN KEY ("FAA_id")
      REFERENCES tbl_FAA_TEST ("FAA_id") MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE tbl_MEDICAL_EXAMINATION
(
  "Med_id"  serial NOT NULL,-- PK
  "Ex_Type" character varying(100),
  "Recent_Exam" date , 
  "Val_Period" date,
    "Traf_id" integer NOT NULL,  -- FK
  CONSTRAINT "PK_Med_id" PRIMARY KEY ("Med_id"),
  CONSTRAINT "FK_Traf_id" FOREIGN KEY ("Traf_id")
      REFERENCES tbl_TRAFFIC_CONTROLLER ("Traf_id") MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE 
  
);
CREATE TABLE tbl_TECHNICIAN
(
  "Tech_id"  serial NOT NULL,-- PK
  "SSN" character varying(100) NOT NULL , 
  CONSTRAINT "PK_Tech_id" PRIMARY KEY ("Tech_id"),
  CONSTRAINT "FK_SSN" FOREIGN KEY ("SSN")
      REFERENCES tbl_WORKERS ("SSN") MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE 
  
);
CREATE TABLE tbl_TRAFFIC_CONTROLLER
(
  "Traf_id"  serial NOT NULL,-- PK
  "SSN" character varying(100) NOT NULL , 
  CONSTRAINT "PK_Traf_id" PRIMARY KEY ("Traf_id"),
  CONSTRAINT "FK_SSN" FOREIGN KEY ("SSN")
      REFERENCES tbl_WORKERS ("SSN") MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE 
  
);
CREATE TABLE tbl_ADDRESS_WORKERS_CE
(
  "Address_id"  integer NOT NULL,-- FK
  "SSN" character varying(100) NOT NULL,  -- FK
  CONSTRAINT "FK_Address_id" FOREIGN KEY ("Address_id")
      REFERENCES tbl_ADDRESS ("Address_id") MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE, 
  CONSTRAINT "FK_SSN" FOREIGN KEY ("SSN")
      REFERENCES tbl_WORKERS ("SSN") MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE 
);
CREATE TABLE tbl_TEL_NO_WORKERS_CE
(
  "Tel_id"  integer NOT NULL,-- FK
  "SSN" character varying(100) NOT NULL,  -- FK
  CONSTRAINT "FK_Tel_id" FOREIGN KEY ("Tel_id")
      REFERENCES tbl_TEL_NO ("Tel_id") MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE, 
  CONSTRAINT "FK_SSN" FOREIGN KEY ("SSN")
      REFERENCES tbl_WORKERS ("SSN") MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE
);
CREATE TABLE tbl_UNION_WORKERS_CE
(
  "Union_id"  integer NOT NULL,-- FK
  "SSN" character varying(100) NOT NULL,  -- FK
  CONSTRAINT "FK_Union_id" FOREIGN KEY ("Union_id")
      REFERENCES tbl_UNION ("Union_id") MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE, 
  CONSTRAINT "FK_SSN" FOREIGN KEY ("SSN")
      REFERENCES tbl_WORKERS ("SSN") MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE 
);
CREATE TABLE tbl_FAA_TEST_TECHNICIAN_CE
(
  "FAA_id"  integer NOT NULL,-- FK
  "Tech_id" integer NOT NULL,  -- FK
  CONSTRAINT "FK_FAA_id" FOREIGN KEY ("FAA_id")
      REFERENCES tbl_FAA_TEST ("FAA_id") MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE, 
  CONSTRAINT "FK_Tech_id" FOREIGN KEY ("Tech_id")
      REFERENCES tbl_TECHNICIAN ("Tech_id") MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE 
);
CREATE TABLE tbl_MODEL_TECHNICIAN_CE
(
  "Model_No" character varying(100) NOT NULL,-- FK
  "Tech_id" integer NOT NULL,  -- FK
  CONSTRAINT "FK_Model_No" FOREIGN KEY ("Model_No")
      REFERENCES tbl_MODEL ("Model_No") MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE, 
  CONSTRAINT "FK_Tech_id" FOREIGN KEY ("Tech_id")
      REFERENCES tbl_TECHNICIAN ("Tech_id") MATCH SIMPLE
      ON UPDATE CASCADE ON DELETE CASCADE 
);

--INSERT INTO AIRPLANE
insert into tbl_AIRPLANE("Name","Model_No") values('Eagle','DC-IO');
insert into tbl_AIRPLANE("Name","Model_No") values(NULL,'DC-I2');
insert into tbl_AIRPLANE("Name","Model_No") values('Winged Beauty','DC-I3');
insert into tbl_AIRPLANE("Name","Model_No") values('Beauty','DC-IO');
insert into tbl_AIRPLANE("Name","Model_No") values('Lady','DC-I1');
insert into tbl_AIRPLANE("Name","Model_No") values('Gentlemen','DC-I4');
insert into tbl_AIRPLANE("Name","Model_No") values('Heaven','DC-I9');
insert into tbl_AIRPLANE("Name","Model_No") values('Rainbow','DC-I7');
insert into tbl_AIRPLANE("Name","Model_No") values(NULL,'DC-I8');
insert into tbl_AIRPLANE("Name","Model_No") values(NULL,'DC-IO');
--INSERT INTO MODEL
insert into tbl_MODEL("Model_No","Capacity","Weight") values('DC-IO','100','79');
insert into tbl_MODEL("Model_No","Capacity","Weight") values('DC-I1','120','95');
insert into tbl_MODEL("Model_No","Capacity","Weight") values('DC-I2','100','79');
insert into tbl_MODEL("Model_No","Capacity","Weight") values('DC-I3','120','95');
insert into tbl_MODEL("Model_No","Capacity","Weight") values('DC-I4','100','79');
insert into tbl_MODEL("Model_No","Capacity","Weight") values('DC-I5','120','95');
insert into tbl_MODEL("Model_No","Capacity","Weight") values('DC-I6','100','79');
insert into tbl_MODEL("Model_No","Capacity","Weight") values('DC-I7','120','95');
insert into tbl_MODEL("Model_No","Capacity","Weight") values('DC-I8','100','79');
insert into tbl_MODEL("Model_No","Capacity","Weight") values('DC-I9','120','95');
-- INSERT INTO WORKERS
insert into tbl_WORKERS("SSN","Name","Surname","Salary") values('89786785745','GülEda','Aydemir','1700');
insert into tbl_WORKERS("SSN","Name","Surname","Salary") values('52753434357','Ayçe','Aydemir','2500');
insert into tbl_WORKERS("SSN","Name","Surname","Salary") values('23423432423','Ergün','Aydemir','6000');
insert into tbl_WORKERS("SSN","Name","Surname","Salary") values('43534345345','Nehir','Aydemir','2500');
insert into tbl_WORKERS("SSN","Name","Surname","Salary") values('65756567657','Deniz','Mutlu','1700');
insert into tbl_WORKERS("SSN","Name","Surname","Salary") values('34534538768','Gülşen','Yılmaz','6000');
insert into tbl_WORKERS("SSN","Name","Surname","Salary") values('42344323242','Eymen','Kara','2500');
insert into tbl_WORKERS("SSN","Name","Surname","Salary") values('54252435234','Murat','Mutlu','6000');
insert into tbl_WORKERS("SSN","Name","Surname","Salary") values('23432424442','Aytaç','Ak','6000');
insert into tbl_WORKERS("SSN","Name","Surname","Salary") values('78543542424','Çiğdem','Balkan','1700');
--INSERT INTO UNION
insert into tbl_UNION("Name") values('A');
insert into tbl_UNION("Name") values('B');
insert into tbl_UNION("Name") values('C');
insert into tbl_UNION("Name") values('D');
insert into tbl_UNION("Name") values('E');
insert into tbl_UNION("Name") values('F');
insert into tbl_UNION("Name") values('G');
insert into tbl_UNION("Name") values('H');
insert into tbl_UNION("Name") values('I');
insert into tbl_UNION("Name") values('J');
--INSERT INTO TELEPHONE
insert into tbl_TEL_NO("Tel_No","Tel_Type") values('05325645789','Cep');
insert into tbl_TEL_NO("Tel_No","Tel_Type") values('05456546544','Ev');
insert into tbl_TEL_NO("Tel_No","Tel_Type") values('12321546879','Cep');
insert into tbl_TEL_NO("Tel_No","Tel_Type") values('45646549789','Cep');
insert into tbl_TEL_NO("Tel_No","Tel_Type") values('32154968465','Cep');
insert into tbl_TEL_NO("Tel_No","Tel_Type") values('54621534665','Ev');
insert into tbl_TEL_NO("Tel_No","Tel_Type") values('45642132165','Cep');
insert into tbl_TEL_NO("Tel_No","Tel_Type") values('21321321321','Cep');
insert into tbl_TEL_NO("Tel_No","Tel_Type") values('45568162134','Cep');
insert into tbl_TEL_NO("Tel_No","Tel_Type") values('78978975431','Cep');
--INSERT INTO ADDRESS
insert into tbl_ADDRESS("Street","Apart_No","District","City","Country") values('Çiçek','12','Beykoz','Istanbul','Turkey');
insert into tbl_ADDRESS("Street","Apart_No","District","City","Country") values('Elma','25','Beykoz','Istanbul','Turkey');
insert into tbl_ADDRESS("Street","Apart_No","District","City","Country") values('Armut','15','Beykoz','Istanbul','Turkey');
insert into tbl_ADDRESS("Street","Apart_No","District","City","Country") values('Ahadudu','48','Maltepe','Istanbul','Turkey');
insert into tbl_ADDRESS("Street","Apart_No","District","City","Country") values('Kiraz','96','Maltepe','Istanbul','Turkey');
insert into tbl_ADDRESS("Street","Apart_No","District","City","Country") values('Dut','78','Göztepe','Istanbul','Turkey');
insert into tbl_ADDRESS("Street","Apart_No","District","City","Country") values('Ceviz','36','Galata','Istanbul','Turkey');
insert into tbl_ADDRESS("Street","Apart_No","District","City","Country") values('Erik','75','Alsancak','Izmir','Turkey');
insert into tbl_ADDRESS("Street","Apart_No","District","City","Country") values('Muz','32','Narlıdere','Izmir','Turkey');
insert into tbl_ADDRESS("Street","Apart_No","District","City","Country") values('Ananas','95','Konak','Izmir','Turkey');
--INSERT INTO FAA_TEST
insert into tbl_FAA_TEST("Plane_Part","FAA_Type","Plane_Score","Hour_Spend","FAA_Date","Reg_No","FAA_Val_Period")
 values('winglet','Type-1','85','2','2016-02-15',5,'2017-10-15');
insert into tbl_FAA_TEST("Plane_Part","FAA_Type","Plane_Score","Hour_Spend","FAA_Date","Reg_No","FAA_Val_Period")
 values('winglet','Type-2','75','3','2016-02-15',6,'2017-08-15');
insert into tbl_FAA_TEST("Plane_Part","FAA_Type","Plane_Score","Hour_Spend","FAA_Date","Reg_No","FAA_Val_Period")
 values('seats','Type-2','65','2','2016-02-15',5,'2017-09-15');
insert into tbl_FAA_TEST("Plane_Part","FAA_Type","Plane_Score","Hour_Spend","FAA_Date","Reg_No","FAA_Val_Period")
 values('turbine engine','Type-2','10','2','2016-02-15',3,'2017-06-15');
insert into tbl_FAA_TEST("Plane_Part","FAA_Type","Plane_Score","Hour_Spend","FAA_Date","Reg_No","FAA_Val_Period")
 values('cockpit','Type-1','10','2','2016-02-15',1,'2017-08-15');
insert into tbl_FAA_TEST("Plane_Part","FAA_Type","Plane_Score","Hour_Spend","FAA_Date","Reg_No","FAA_Val_Period")
 values('fuselage','Type-2','65','3','2016-02-15',2,'2017-12-15');
insert into tbl_FAA_TEST("Plane_Part","FAA_Type","Plane_Score","Hour_Spend","FAA_Date","Reg_No","FAA_Val_Period")
 values('rudder','Type-1','85','4','2016-02-15',10,'2017-11-15');
insert into tbl_FAA_TEST("Plane_Part","FAA_Type","Plane_Score","Hour_Spend","FAA_Date","Reg_No","FAA_Val_Period")
 values('winglet','Type-1','85','4','2016-02-15',4,'2017-07-15');
insert into tbl_FAA_TEST("Plane_Part","FAA_Type","Plane_Score","Hour_Spend","FAA_Date","Reg_No","FAA_Val_Period")
 values('winglet','Type-1','85','4','2016-02-15',8,'2017-07-15');
insert into tbl_FAA_TEST("Plane_Part","FAA_Type","Plane_Score","Hour_Spend","FAA_Date","Reg_No","FAA_Val_Period")
 values('turbine engine','Type-10','35','4','2016-02-15',9,'2017-09-15');
--INSERT INTO MAINTENANCE
insert into tbl_MAINTENANCE("Main_Type","Broken_Part","Broken_Reason","Main_Period","Reg_No","FAA_id")
 values('Type-2','turbine engine','broken','2016-06-15',3,4);
insert into tbl_MAINTENANCE("Main_Type","Broken_Part","Broken_Reason","Main_Period","Reg_No","FAA_id")
 values('Type-2','cockpit','broken','2016-08-15',1,5);

insert into tbl_MAINTENANCE("Main_Type","Broken_Part","Broken_Reason","Main_Period","Reg_No","FAA_id")
 values('Type-3','turbine engine','fired','2016-09-15',9,10);
--INSERT INTO TECHINICIAN
insert into tbl_TECHNICIAN("SSN") values('89786785745');
insert into tbl_TECHNICIAN("SSN") values('23423432423');
insert into tbl_TECHNICIAN("SSN") values('65756567657');
insert into tbl_TECHNICIAN("SSN") values('42344323242');
insert into tbl_TECHNICIAN("SSN") values('23432424442');
--INSERT INTO TRAFFIC CONTROLLER
insert into tbl_TRAFFIC_CONTROLLER("SSN") values('52753434357');
insert into tbl_TRAFFIC_CONTROLLER("SSN") values('43534345345');
insert into tbl_TRAFFIC_CONTROLLER("SSN") values('34534538768');
insert into tbl_TRAFFIC_CONTROLLER("SSN") values('54252435234');
insert into tbl_TRAFFIC_CONTROLLER("SSN") values('78543542424');
--INSERT INTO MEDICAL EXAMINATION
insert into tbl_MEDICAL_EXAMINATION("Ex_Type","Recent_Exam","Val_Period","Traf_id") values('eyes','2017-02-15','2017-06-15',1); -- 4 mth
insert into tbl_MEDICAL_EXAMINATION("Ex_Type","Recent_Exam","Val_Period","Traf_id") values('ears','2017-01-30','2017-08-30',1); -- 7 mth
insert into tbl_MEDICAL_EXAMINATION("Ex_Type","Recent_Exam","Val_Period","Traf_id") values('heart','2017-03-15','2017-09-15',2);-- 6 mth
insert into tbl_MEDICAL_EXAMINATION("Ex_Type","Recent_Exam","Val_Period","Traf_id") values('teeth','2017-01-03','2017-09-03',2);-- 8 mht
insert into tbl_MEDICAL_EXAMINATION("Ex_Type","Recent_Exam","Val_Period","Traf_id") values('check-up','2016-01-13','2016-11-13',3);--10 mth
insert into tbl_MEDICAL_EXAMINATION("Ex_Type","Recent_Exam","Val_Period","Traf_id") values('eyes','2016-02-15','2018-02-15',4);-- 2 years
insert into tbl_MEDICAL_EXAMINATION("Ex_Type","Recent_Exam","Val_Period","Traf_id") values('ears','2016-02-15','2018-02-15',4);-- 2 years
insert into tbl_MEDICAL_EXAMINATION("Ex_Type","Recent_Exam","Val_Period","Traf_id") values('ears','2017-02-15','2017-08-15',5);-- 6 mth 
insert into tbl_MEDICAL_EXAMINATION("Ex_Type","Recent_Exam","Val_Period","Traf_id") values('heart','2015-01-15','2018-01-15',5);-- 3 years
insert into tbl_MEDICAL_EXAMINATION("Ex_Type","Recent_Exam","Val_Period","Traf_id") values('heart','2016-01-15','2018-01-15',1);-- 2 years
--INSERT INTO tbl_ADDRESS_WORKERS_CE
insert into tbl_ADDRESS_WORKERS_CE("Address_id","SSN") values('1','89786785745');
insert into tbl_ADDRESS_WORKERS_CE("Address_id","SSN") values('1','52753434357');
insert into tbl_ADDRESS_WORKERS_CE("Address_id","SSN") values('1','23423432423');
insert into tbl_ADDRESS_WORKERS_CE("Address_id","SSN") values('1','43534345345');
insert into tbl_ADDRESS_WORKERS_CE("Address_id","SSN") values('5','65756567657');
insert into tbl_ADDRESS_WORKERS_CE("Address_id","SSN") values('2','42344323242');
insert into tbl_ADDRESS_WORKERS_CE("Address_id","SSN") values('3','23432424442');
insert into tbl_ADDRESS_WORKERS_CE("Address_id","SSN") values('8','34534538768');
insert into tbl_ADDRESS_WORKERS_CE("Address_id","SSN") values('9','54252435234');
insert into tbl_ADDRESS_WORKERS_CE("Address_id","SSN") values('10','78543542424');
--INSERT INTO tbl_TEL_NO_WORKERS_CE
insert into tbl_TEL_NO_WORKERS_CE("Tel_id","SSN") values('1','89786785745');
insert into tbl_TEL_NO_WORKERS_CE("Tel_id","SSN") values('2','89786785745');
insert into tbl_TEL_NO_WORKERS_CE("Tel_id","SSN") values('1','52753434357');
insert into tbl_TEL_NO_WORKERS_CE("Tel_id","SSN") values('2','52753434357');
insert into tbl_TEL_NO_WORKERS_CE("Tel_id","SSN") values('3','23423432423');
insert into tbl_TEL_NO_WORKERS_CE("Tel_id","SSN") values('4','43534345345');
insert into tbl_TEL_NO_WORKERS_CE("Tel_id","SSN") values('10','65756567657');
insert into tbl_TEL_NO_WORKERS_CE("Tel_id","SSN") values('6','65756567657');
insert into tbl_TEL_NO_WORKERS_CE("Tel_id","SSN") values('9','42344323242');
insert into tbl_TEL_NO_WORKERS_CE("Tel_id","SSN") values('8','23432424442');
insert into tbl_TEL_NO_WORKERS_CE("Tel_id","SSN") values('7','34534538768');
insert into tbl_TEL_NO_WORKERS_CE("Tel_id","SSN") values('6','54252435234');
insert into tbl_TEL_NO_WORKERS_CE("Tel_id","SSN") values('5','78543542424');
--INSERT INTO tbl_FAA_TEST_TECHNICIAN_CE
insert into tbl_FAA_TEST_TECHNICIAN_CE("FAA_id","Tech_id") values('1','1');
insert into tbl_FAA_TEST_TECHNICIAN_CE("FAA_id","Tech_id") values('2','2');
insert into tbl_FAA_TEST_TECHNICIAN_CE("FAA_id","Tech_id") values('3','3');
insert into tbl_FAA_TEST_TECHNICIAN_CE("FAA_id","Tech_id") values('3','1');
insert into tbl_FAA_TEST_TECHNICIAN_CE("FAA_id","Tech_id") values('4','4');
insert into tbl_FAA_TEST_TECHNICIAN_CE("FAA_id","Tech_id") values('4','2');
insert into tbl_FAA_TEST_TECHNICIAN_CE("FAA_id","Tech_id") values('5','5');
insert into tbl_FAA_TEST_TECHNICIAN_CE("FAA_id","Tech_id") values('6','4');
insert into tbl_FAA_TEST_TECHNICIAN_CE("FAA_id","Tech_id") values('7','1');
insert into tbl_FAA_TEST_TECHNICIAN_CE("FAA_id","Tech_id") values('8','2');
insert into tbl_FAA_TEST_TECHNICIAN_CE("FAA_id","Tech_id") values('9','5');
insert into tbl_FAA_TEST_TECHNICIAN_CE("FAA_id","Tech_id") values('9','4');
insert into tbl_FAA_TEST_TECHNICIAN_CE("FAA_id","Tech_id") values('10','3');
--INSERT INTO tbl_MODEL_TECHNICIAN_CE
insert into tbl_MODEL_TECHNICIAN_CE("Model_No","Tech_id") values('DC-IO','1');
insert into tbl_MODEL_TECHNICIAN_CE("Model_No","Tech_id") values('DC-IO','2');
insert into tbl_MODEL_TECHNICIAN_CE("Model_No","Tech_id") values('DC-I1','1');
insert into tbl_MODEL_TECHNICIAN_CE("Model_No","Tech_id") values('DC-I2','3');
insert into tbl_MODEL_TECHNICIAN_CE("Model_No","Tech_id") values('DC-I3','2');
insert into tbl_MODEL_TECHNICIAN_CE("Model_No","Tech_id") values('DC-I3','4');
insert into tbl_MODEL_TECHNICIAN_CE("Model_No","Tech_id") values('DC-I4','5');
insert into tbl_MODEL_TECHNICIAN_CE("Model_No","Tech_id") values('DC-I5','3');
insert into tbl_MODEL_TECHNICIAN_CE("Model_No","Tech_id") values('DC-I5','4');
insert into tbl_MODEL_TECHNICIAN_CE("Model_No","Tech_id") values('DC-I6','5');
insert into tbl_MODEL_TECHNICIAN_CE("Model_No","Tech_id") values('DC-I6','3');
insert into tbl_MODEL_TECHNICIAN_CE("Model_No","Tech_id") values('DC-I7','5');
insert into tbl_MODEL_TECHNICIAN_CE("Model_No","Tech_id") values('DC-I8','1');
insert into tbl_MODEL_TECHNICIAN_CE("Model_No","Tech_id") values('DC-I8','4');
insert into tbl_MODEL_TECHNICIAN_CE("Model_No","Tech_id") values('DC-I9','2');
--INSERT INTO tbl_UNION_WORKERS_CE
insert into tbl_UNION_WORKERS_CE("Union_id","SSN") values('1','89786785745');
insert into tbl_UNION_WORKERS_CE("Union_id","SSN") values('1','52753434357');
insert into tbl_UNION_WORKERS_CE("Union_id","SSN") values('1','23423432423');
insert into tbl_UNION_WORKERS_CE("Union_id","SSN") values('1','43534345345');
insert into tbl_UNION_WORKERS_CE("Union_id","SSN") values('2','65756567657');
insert into tbl_UNION_WORKERS_CE("Union_id","SSN") values('2','42344323242');
insert into tbl_UNION_WORKERS_CE("Union_id","SSN") values('3','23432424442');
insert into tbl_UNION_WORKERS_CE("Union_id","SSN") values('3','34534538768');
insert into tbl_UNION_WORKERS_CE("Union_id","SSN") values('4','54252435234');
insert into tbl_UNION_WORKERS_CE("Union_id","SSN") values('5','78543542424');


--QUERY 1
SELECT DISTINCT a."Reg_No" 
FROM tbl_AIRPLANE AS a 
WHERE NOT a."Reg_No" in (SELECT b."Reg_No" FROM tbl_MAINTENANCE as b)

--QUERY 2
SELECT  a."Reg_No" , a."Name"
FROM tbl_AIRPLANE AS a 
WHERE (NOT a."Reg_No" in (SELECT b."Reg_No" FROM tbl_MAINTENANCE as b)) AND (a."Name" IS NOT NULL)

--QUERY 3
SELECT a."Name", a."Surname"
FROM tbl_Workers as a 
WHERE a."SSN" in (SELECT b."SSN" FROM tbl_ADDRESS_WORKERS_CE as b 
			WHERE b."Address_id" in (Select c."Address_id"
from tbl_Address as c
where c."District" in (Select c."District" from tbl_address 
					as c Group by c."District" having count( "District") >1)))
					
--QUERY 4
Select d."Name" ,d."Surname"
from tbl_workers as d
where d."SSN" in (Select c."SSN"
from tbl_TRAFFIC_CONTROLLER as c
where c."Traf_id" in (SELECT  a."Traf_id"
FROM tbl_traffic_controller AS a 
WHERE (NOT a."Traf_id" in (SELECT b."Traf_id" FROM tbl_MEDICAL_EXAMINATION as b))))

--QUERY 5
Select c."Union_id",count(c."Union_id") from tbl_UNION_WORKERS_CE 
					as c Group by c."Union_id" having count( "Union_id") >-1 Order by count( "Union_id") ASC 
					
--QUERY 6
Select MAX(e."Model_No") from tbl_airplane as e where e."Reg_No" in (Select d."Reg_No" from tbl_maintenance as d)

--QUERY 7
 (Select (d."Union_id") from tbl_UNION_WORKERS_CE as d where d."SSN" in  (Select c."SSN" from tbl_technician as c))
--QUERY 8

--QUERY 9

Select f."Plane_Part", MAX(f."Plane_Score") from tbl_FAA_TEST as f group by f."Plane_Part",f."Plane_Score" having f."Plane_Score">70

--QUERY 10

 Select MAX(d."Broken_Reason") from tbl_Maintenance as d Group by (d."Broken_Reason") having count((d."Broken_Reason"))>1
 
