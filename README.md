# ktane_display
An exploratory project to render some stats from the game Keep Talking and Nobody Explodes on a web server.

## Build
node-gyp is required

```
cd display
npm i
```

## Usage
Open the game then run `node index.js`

Node access the game memory directly, pointers where discovered with Cheat Engine with Pointer Scan, will stop working at any time since pointer based access is brittle. Inject code into a dll can be a better alternative.
