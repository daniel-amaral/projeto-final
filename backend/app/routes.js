'use strict'

module.exports = function(app, cors){

    var sequelize = require('./orm.js')()

    sequelize
        .authenticate()
        .then(() => {
        console.log('DATABASE: Connection has been established successfully.');
        })
        .catch(err => {
        console.error('Unable to connect to the database:', err);
        });

    app.use(cors());
    app.options('*', cors());
    
    app.post('/api/helium-measure-echo', (req, res) => {
        let body = req.body
        console.log(`machine: ${body.machine}, level: ${body.heliumLevel}`)
        res.sendStatus(200)
    })

    app.get('/api/find-all-helium-measures/:machineName', (req, res) => {
        sequelize.query(
            `SELECT * FROM helium_measure WHERE machine_id =
                (SELECT id FROM machine WHERE machine_name = ${req.params.machineName})`,
            { type: sequelize.QueryTypes.SELECT })
                .then(result => {
                    res.send(result)
                })
    })

    app.get('/api/test', (req, res) => {
        sequelize.query(
            `SELECT * FROM helium_measure WHERE machine_id =
                (SELECT id FROM machine WHERE machine_name = 'arduino-sample')`,
            { type: sequelize.QueryTypes.SELECT })
                .then(result => {
                    res.send(result)
                })
    })

    app.post('/api/helium-measure', (req, res) => {
        let body = req.body
        console.log(`machine: ${body.machine}, level: ${body.heliumLevel}`)
        res.sendStatus(200)
    })
}