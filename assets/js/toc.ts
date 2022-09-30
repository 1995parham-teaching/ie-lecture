import * as params from "@params";

function toc(titles: [string]) {
  console.log(titles);
  let sections = document.getElementsByClassName("toc");

  for (let section of sections) {
    if (section instanceof HTMLElement) {
      const titlesListElement = document.createElement("ul");

      for (let title of titles) {
        let node = document.createElement("li");

        if (section.dataset.selected && section.dataset.selected === title) {
          node.className += "hl-material";
        }

        if (
          section.dataset.selected &&
          titles[parseInt(section.dataset.selected)] === title
        ) {
          node.className += "hl-material";
        }

        node.appendChild(document.createTextNode(title));
        titlesListElement.appendChild(node);
      }

      section.appendChild(titlesListElement);
    }
  }
}

toc(params.topics);
