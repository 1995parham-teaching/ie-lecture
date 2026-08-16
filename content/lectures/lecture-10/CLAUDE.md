# Lecture 10 — Virtualization

44 slides, 2 vertical stacks. Topics (TOC indices): `0` IaaS, PaaS, SaaS ·
`1` Virtual Machine · `2` Containers.

Arc: the NIST cloud-computing definition → IaaS/PaaS/SaaS → virtualization
techniques → hypervisors → CPU and IO virtualization → QEMU → containers →
containers vs VMs → namespaces → container engines → Docker (images,
containers, Dockerfile, layers, CLI, volumes, Compose).

## Facts worth not re-deriving

- **VirtualBox and VMware are not IaaS providers.** They are hypervisors. The
  deck used to list them under IaaS.
- The runtime is **rkt**, not "rtk", and it is discontinued. containerd and
  CRI-O are the current ones and are on the slide.
- The Compose sample **must parse**. The one in the deck was unparseable —
  `db` indented three spaces, `wordpress` two. Run any YAML you add through a
  parser.

## The Dockerfile sample

Rewritten and pinned; do not casually update it:

- Base is `ubuntu:24.04`, **not** `ubuntu:latest` — a moving base makes the
  layer-caching slide meaningless.
- `apt-key` was removed in Ubuntu 22.04. The sample uses `/etc/apt/keyrings`
  with `signed-by=`.
- MongoDB is 8.0 (was 3.2).
- `apt-get update` runs **before** `apt-get install`, in the same layer.
