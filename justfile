default:
    @just --list

# install required nodejs pacakges
install:
    npm install --include=dev

# run the dev server
dev: install
    hugo server
