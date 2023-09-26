default:
    @just --list

# install required nodejs pacakges
install:
    npm install --include=dev

# run the dev server and you can give lecture
dev: install
    hugo server
