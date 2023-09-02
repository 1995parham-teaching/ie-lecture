default:
    @just --list

# install required nodejs pacakges
install:
    npm install

# run the dev server
dev: install
    hugo server
