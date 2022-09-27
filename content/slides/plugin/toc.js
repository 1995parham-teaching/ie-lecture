/*
 * +===============================================
 * | Author:        Parham Alvani (parham.alvani@gmail.com)
 * |
 * | Creation Date: 03-08-2017
 * |
 * | File Name:     toc.js
 * +===============================================
 */
const toc = {
  initToCOnLoad: function (titles) {
    let sections = document.getElementsByClassName('toc')

    for (let section of sections) {
      const titlesListElement = document.createElement('ul');

      for (let title of titles) {
        let node = document.createElement('li');

        if (section.dataset.selected && section.dataset.selected === title) {
          node.className += 'hl-material'
        }

        if (section.dataset.selected && titles[parseInt(section.dataset.selected)] === title) {
          node.className += 'hl-material'
        }

        node.appendChild(document.createTextNode(title));
        titlesListElement.appendChild(node);
      }

      section.appendChild(titlesListElement);
    }
  }
}
