import Reveal from "reveal.js";
import hljs from 'highlight.js';


new Reveal().initialize({
  history: true,
  slideNumber: true,
  dependencies: [
    {
      async: true,
      callback: function() { hljs.initHighlightingOnLoad(); }
    },
  ],
});
