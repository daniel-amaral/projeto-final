'use strict'

const express = require('express')
const cors = require('cors')
const bodyParser = require('body-parser')

const app = express()
const port = 3000

app.use(express.static(__dirname + '/public'))
app.use(bodyParser.json());

app.use(function(req, res, next) {
	res.set('Access-Control-Allow-Origin', '*');
	res.set('Access-Control-Allow-Methods', 'GET, POST, DELETE, PUT');
	res.set('Access-Control-Allow-Headers', 'Origin, Accept, Content-Type, X-Requested-With, X-CSRF-Token'); //needs to work with DELETE verb
	next();
});

app.post('/sample-post', function(req, res){

	let machine = req.body.machine
	let heliumLevel = req.body.heliumLevel

	console.log('machine: ', machine)
	console.log('heliumLevel: ', heliumLevel)
	console.log()
		
	res.json({
		code: 200,
		status: 'OK',
		body: req.body
	})
	return;
})


require('./app/routes.js')(app, cors)


app.listen(port, () => {
	console.log('\nApplication running on http://localhost:%d', port)
	console.log('\n(Server started, use Ctrl+C to stop and go back to the console...)\n')
});