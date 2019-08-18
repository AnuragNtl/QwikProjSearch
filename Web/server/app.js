var express = require("express");
var bodyParser = require('body-parser');
var cookieParser = require('cookie-parser');

var app = express();

app.use(cookieParser());
app.use(bodyParser());

app.get("/getAllProjects", function(req,res) {
	res.send([]);
});

app.post("/getAllRegexTemplates", function(req, res) {

});

app.get("/getRegexTemplateByName", function(req, res) {

});

app.post("/applyToRegexTemplate", function(req, res) {

});

app.get("/findInProjects/:regextemplateId", function(req, res) {

});

app.post("/findInProjects", function(req, res) {

});


app.put("/addProject/", function(req, res) {

});

app.

app.listen(8096, function(err) {
	console.log("started");
});
