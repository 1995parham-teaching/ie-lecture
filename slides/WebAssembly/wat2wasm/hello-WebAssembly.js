fetch('addTwoNum.wasm')
// take the raw binary file and put that into an array buffer 
.then(response => response.arrayBuffer())
// take the bytes and instantiate it through webassembly
.then(bytes => WebAssembly.instantiate(bytes))
// take the reults and use the instance exports functions
.then(results => results.instance.exports.add(14, 5))
// display it in HTML
.then (addResult => document.body.textContent = `Congrats. Your wrote your first WebAssembly program :)  Addition result: ${addResult}`)