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

Both scripts were run end to end, and the diagrams drawn from those runs:

- `create_container.sh`: piped into `bash -x` in a privileged `docker:27-cli`
  container (plus `apk add bash util-linux iproute2 sudo tar`) with the host's
  `docker.sock` mounted, so the `docker run`/`docker export` lines really ran.
  Docker Hub no longer has a `centos` image, and `quay.io/centos/centos:stream9`
  has no `ps`, `ip` or `hostname`, so step 1 installs them before exporting.
  Inside: `hostname` is `mohammad`, `ps aux` shows `bash` as PID 1, `ip a`
  shows `lo` down (plus the kernel's tunnel stubs), `ls /` is the image and
  `/proc/mounts` lists only `/` and `/proc`. Two traps found on the way:
  `pivot_root` needs the new root to be a mount point (hence the bind mount
  onto itself), and `umount` reads `/proc/self/mounts`, so `/proc` must be
  mounted **before** `umount -l /oldroot` or the host's root silently stays
  mounted at `/oldroot`.
- `play_with_netns.sh`: run with `bash -x` in a privileged `alpine:3.20`
  container (plus `iproute2 iptables`) on a user-defined Docker network. Both
  halves ping between the namespaces; `ping 1.1.1.1` from `parham` gets
  replies, and fails once the MASQUERADE rule is deleted; a second container
  on the network fetched a page served by `busybox httpd` inside `mohammad`
  through the DNAT rule. The `FORWARD ACCEPT` rules matter on a host running
  Docker, whose FORWARD policy is DROP.
