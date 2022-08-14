const express = require('express');
const morgan = require('morgan');
const app = express();
const port = 3000;

app.use(morgan('dev'));
app.use(express.urlencoded({ extended: false }));
app.use(express.json());

app.use('/sqladd', require('./routes/sql.js'));

app.listen(port, () => {
   console.log('server node_counter started on localhost:' + port);
});
