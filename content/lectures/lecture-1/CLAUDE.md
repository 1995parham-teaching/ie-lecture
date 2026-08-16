# Lecture 1 — Introduction

The opening session: who the instructor is, what the course covers, a short
history of the web, and the grading policy. 44 slides across 35 horizontal
positions, three of them vertical stacks.

Topics (TOC indices): `0` Instructor · `1` Course Overview · `2` World-Wide Web ·
`3` Syllabus · `4` Course Policies.

## The six live slides

Each is a real demo, not a screenshot, and each depends on the network or the
browser at lecture time:

| Slide                              | Demo                                                 |
| ---------------------------------- | ---------------------------------------------------- |
| WWW: static                        | `<iframe>` of `https://example.com/`                 |
| WWW: interactive                   | a button that moves itself on click                  |
| WWW: distributed                   | `fetch()` against `swapi.dev`                        |
| You Are Already Running One        | `navigator.*` — browser, viewport, language, cookies |
| Every Browser Claims to Be Mozilla | the raw `navigator.userAgent`                        |
| So Is This Deck                    | Navigation and Resource Timing for this very page    |

`example.com` sends no framing headers and `swapi.dev` sends
`access-control-allow-origin: *`, so both work in principle — but swapi.dev is
behind CloudFront, which is not always reachable from the classroom. The fetch
has a `.catch` that prints the failure on the slide; keep it.

The `navigator` slides need no network and cannot fail. The browser-detection
list is **order-sensitive**: Edge's user-agent contains `Chrome`, and Chrome's
contains `Safari`, so the patterns must stay in the order Firefox → Edg →
Chrome → Version/Safari. It falls back to "something exotic" rather than
throwing.

## Facts worth not re-deriving

- The grading table sums to 100 (35 midterm / 35 final / 30 homework), with a
  40% minimum on each exam.
- The nine timeline dates were each checked: 1989 proposal at CERN (Mike Sendall
  really did write "Vague, but exciting…" on it), 1990 WorldWideWeb the
  browser-editor, Aug 1991 first public site, 1993 Mosaic and CERN's public-domain
  release, Oct 1994 W3C and Håkon Wium Lie's CSS proposal, May 1995 JavaScript,
  June 1999 RFC 2616, Sept 2008 Chrome and V8, 2015 HTTP/2 and 2022 HTTP/3.
- "Tim Berners-Lee, 1989" is correct — the proposal was March 1989, at CERN.
- The timeline table is set to `font-size: 0.7em` **deliberately**. At full size
  most of its nine rows wrap to two lines and the table runs past the 700px
  slide. Do not remove that style without re-checking the height.

## Two things that must stay in step

**The ten questions and the "Who Answers What" table.** Every question maps to a
lecture that exists; that is the whole point of the pair. Q9 used to be "How does
Gmail offline work?", which no lecture answered — it is now the deployment
question, and Q10 is security. If you add or drop a lecture, fix both slides.

**The syllabus list, the README, and the home page.** All three now agree:
lectures 1–7 and 9–11 are taught in class, 8 (CGI) and the unnumbered decks are
extra material on the site. The "Also on the Site, Not in Class" slide is what
keeps lecture 8 honest — it is in the repo, so it is acknowledged, but it is not
claimed as a session.
