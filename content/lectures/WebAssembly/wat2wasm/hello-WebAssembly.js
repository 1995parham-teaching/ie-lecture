fetch("addTwoNum.wasm")
  // stop on a 404 instead of handing an HTML error page to WebAssembly
  .then((response) => {
    if (!response.ok) {
      throw new Error(`${response.status} ${response.statusText}`);
    }
    // take the raw binary file and put that into an array buffer
    return response.arrayBuffer();
  })
  // take the bytes and instantiate it through webassembly
  .then((bytes) => WebAssembly.instantiate(bytes))
  // take the results and use the instance exports functions
  .then((results) => results.instance.exports.add(14, 5))
  // display it in HTML
  .then(
    (addResult) =>
      (document.body.textContent = `Congrats. You wrote your first WebAssembly program :)  Addition result: ${addResult}`),
  )
  // print the failure instead of leaving an empty page
  .catch((err) => {
    // fetch() refuses file:// URLs, so opening index.html from disk lands here
    const hint =
      location.protocol === "file:"
        ? " Serve this folder over HTTP (python3 -m http.server) and open http://localhost:8000/"
        : "";
    document.body.textContent = `Could not load addTwoNum.wasm: ${err}.${hint}`;
    console.error(err);
  });
