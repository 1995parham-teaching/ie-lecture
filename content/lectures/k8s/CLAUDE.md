# Cloud Native and Kubernetes

An extra deck (`lecture: false`) that is really an **index page**, not a
presentation: 4 slides linking out to four PDF decks and two shell scripts.

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
  _Containers from Scratch_ — they build a container from namespaces and cgroups
  by hand. They are Linux-only and need root; they will not run on the macOS dev
  machine.
- The last slide points at lecture 10 (Virtualization), which teaches the
  namespace, cgroup and layered-filesystem primitives these depend on. Keep that
  cross-reference alive if either deck is reorganised.
