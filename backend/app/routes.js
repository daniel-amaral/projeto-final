'use strict'

module.exports = function(app, cors){

    var sequelize = require('./orm.js')()

    sequelize
        .authenticate()
        .then(() => {
        console.log('Connection has been established successfully.');
        })
        .catch(err => {
        console.error('Unable to connect to the database:', err);
        });

    app.use(cors());
    app.options('*', cors());
    
    app.post('/api/helium-measure', (req, res) => {
        let body = req.body
        console.log(`machine: ${body.machine}, level: ${body.heliumLevel}`)
        res.sendStatus(200)
    })
}