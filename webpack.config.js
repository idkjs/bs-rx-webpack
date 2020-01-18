const path = require('path');

module.exports = {
  entry: './lib/js/demos/Demo.bs.js',
  mode: 'development',
  output: {
    path: path.join(__dirname, "build"),
    filename: 'index.js',
  },
};