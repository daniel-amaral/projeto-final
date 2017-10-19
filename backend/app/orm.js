'use strict'

module.exports = function() {
    
    const username = 'root'
    const password = 'root'
    const database = 'MRI'
    const host = 'localhost'
    // const host = 'ec2-54-207-124-79.sa-east-1.compute.amazonaws.com'
    const port = 3306

    var Sequelize = require('sequelize')

    var instance = new Sequelize(database, username, password, {
        host: host,
        dialect: 'mysql',
    
        pool: {
            max: 5,
            min: 0,
            idle: 10000
        }
    })

    return instance
}

