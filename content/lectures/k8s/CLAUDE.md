# Cloud Native and Kubernetes

An extra deck (`lecture: false`) that is really an **index page**, not a
presentation: 6 slides linking out to four PDF decks and two shell scripts,
with a diagram of each script.

```
lecture1/CloudNativeGolang.pdf
lecture2/Containers.pdf
lecture3/ContainersFromScratch.pdf   + create_container.sh, play_with_netns.sh
lecture4-5/dockerInPractice.pdf
```

`topics: []` is deliberate — an empty list makes the generated title card skip
the topics line, so there is nothing to keep in sync. Do not add topics unless
the deck grows real sections.

## Notes

- The PDFs are **binary artifacts with no source in this repo**. They cannot be
  edited here; treat them as fixed content and only change the surrounding page.
- The two shell scripts are meant to be run while reading
  _Containers from Scratch_ — they build a container from namespaces and
  `pivot_root` by hand (no cgroups, despite what the page used to say). They
  are Linux-only and need root; they will not run on the macOS dev machine.
- The last slide points at lecture 10 (Virtualization), which teaches the
  namespace, cgroup and layered-filesystem primitives these depend on. Keep that
  cross-reference alive if either deck is reorganised.

## Diagrams

Hand-written SVGs in `img/`, drawn for the league background (see the root
`CLAUDE.md`). They have no draw.io source:

| File                         | Slide                                  |
| ---------------------------- | -------------------------------------- |
| `container-from-scratch.svg` | create_container.sh — the five steps   |
| `netns.svg`                  | play_with_netns.sh — veth, then bridge |

Both were checked by running the scripts' commands in a privileged
`alpine:3.20` container (an alpine export instead of centos):

- `create_container.sh` works once its two broken `mount` lines are written as
  `mount --bind /mycontainer /mycontainer`. As committed, line 12 has no
  target and both lines say `mycontainers` while the directory is
  `mycontainer`. Inside, `hostname` is `mohammad`, `ps` shows the shell as
  PID 1, and `ip a` shows only `lo` (and the kernel's tunnel stubs), all down.
- `play_with_netns.sh`: the veth-pair half pings. The bridge half leaves
  `parham-end` and `mohammad-end` without addresses and down, so nothing
  pings; and its NAT rules also need a gateway address on `my-bridge`, a
  default route in each namespace and `ip_forward`. The diagram draws those
  missing steps in yellow and says they are not in the script.
