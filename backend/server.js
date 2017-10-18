'use strict'

const express = require('express')
const bodyParser = require('body-parser')

const app = express()
const port = 3000

app.use(bodyParser.json()); // to parse the http requisitions

app.get('/', function(req, res){
	console.log("requisition retrieved")
})

app.post('/sample-post', function(req, res){

	let machine = req.body.machine
	let heliumLevel = req.body.heliumLevel

	console.log('machine: ', machine)
	console.log('heliumLevel: ', heliumLevel)
		
	res.json({
		code: 200,
		status: 'OK',
		body: req.body
	})
	return;
})

let writeOnFile = function (filename, output) {
	fs.writeFile(__dirname + '/' + filename , output, function(err) {
	    if(err) {
	        return console.log(err)
	    }

	    console.log("The file was saved!")
	})
}


app.listen(port, () => {
	console.log('\nServer running at http://localhost:' + port +'\n')
});