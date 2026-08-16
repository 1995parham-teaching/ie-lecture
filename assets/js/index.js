import Reveal from "reveal.js";
import Highlight from "reveal.js/plugin/highlight";
import Notes from "reveal.js/plugin/notes";
import Search from "reveal.js/plugin/search";
import Zoom from "reveal.js/plugin/zoom";

new Reveal({
  // notes opens the speaker view with "s", search filters slides with
  // "ctrl+shift+f", and zoom magnifies a region with "alt+click"
  plugins: [Highlight, Notes, Search, Zoom],
  // hash keeps a stable url per slide, so a single slide can be shared
  hash: true,
  slideNumber: true,
}).initialize();
