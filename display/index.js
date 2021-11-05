const express = require('express');
const hbs = require('express-hbs');
const { fetchKtaneInformation } = require('./src/game');

const app = express();
const port = 3000;

app.use(express.json());
app.engine('hbs', hbs.express4());
app.set('view engine', 'hbs');
app.set('views', __dirname + '/views');

app.get('/', (req, res) => {
	res.render('index');
});

app.get('/events', (req, res) => {
	const headers = {
		'Content-Type': 'text/event-stream',
		'Connection': 'keep-alive',
		'Cache-Control': 'no-cache'
	};

	res.writeHead(200, headers);

	const timer = setInterval(() => {
		res.write(`data: ${JSON.stringify(fetchKtaneInformation())}\n\n`);
	}, 100);

	res.on('close', () => clearInterval(timer));
});

app.listen(port, () => {
	console.log(`Ktane display app listening at http://localhost:${port}`)
});