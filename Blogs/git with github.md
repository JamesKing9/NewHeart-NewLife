# A successful Git branching model

​    ![img](http://nvie.com/img/nvie-small@2x.jpg)
​    By [Vincent Driessen](http://nvie.com/about/)
​    on Tuesday, January 05, 2010

In this post I present the development model that I’ve introduced for some ofmy projects (both at work and private) about a year ago, and which has turnedout to be very successful. I’ve been meaning to write about it for a while now,but I’ve never really found the time to do so thoroughly, until now. I won’ttalk about any of the projects’ details, merely about the branching strategyand release management.

>  ![img](http://nvie.com/img/git-model@2x.png)

## Why git? 

For a thorough discussion on the pros and cons of Git compared to centralizedsource code control systems, [see](http://whygitisbetterthanx.com/) the[web](http://git.or.cz/gitwiki/GitSvnComparsion). There are plenty of flamewars going on there. As a developer, I prefer Git above all other tools aroundtoday. Git really changed the way developers think of merging and branching.From the classic CVS/Subversion world I came from, merging/branching has alwaysbeen considered a bit scary (“beware of merge conflicts, they bite you!”) andsomething you only do every once in a while.

But with Git, these actions are extremely cheap and simple, and they areconsidered one of the core parts of your *daily* workflow, really. For example,in CVS/Subversion [books](http://svnbook.red-bean.com), branching and mergingis first discussed in the later chapters (for advanced users), while in[every](http://book.git-scm.com)[Git](http://pragprog.com/titles/tsgit/pragmatic-version-control-using-git)[book](http://github.com/progit/progit), it’s already covered in chapter3 (basics).

As a consequence of its simplicity and repetitive nature, branching and mergingare no longer something to be afraid of. Version control tools are supposed toassist in branching/merging more than anything else.

Enough about the tools, let’s head onto the development model. The model thatI’m going to present here is essentially no more than a set of procedures thatevery team member has to follow in order to come to a managed softwaredevelopment process.

## Decentralized but centralized

The repository setup that we use and that works well with this branching model,is that with a central “truth” repo. Note that this repo is only *considered*to be the central one (since Git is a DVCS, there is no such thing as a centralrepo at a technical level). We will refer to this repo as `origin`, since thisname is familiar to all Git users.

>  ![img](http://nvie.com/img/centr-decentr@2x.png)

Each developer pulls and pushes to origin. But besides the centralizedpush-pull relationships, each developer may also pull changes from other peersto form sub teams. For example, this might be useful to work together with twoor more developers on a big new feature, before pushing the work in progress to`origin` prematurely. In the figure above, there are subteams of Alice and Bob,Alice and David, and Clair and David.

Technically, this means nothing more than that Alice has defined a Git remote,named `bob`, pointing to Bob’s repository, and vice versa.

## The main branches 

![img](http://nvie.com/img/main-branches@2x.png)

At the core, the development model is greatly inspired by existing models outthere. The central repo holds two main branches with an infinite lifetime:

- `master`
- `develop`

The `master` branch at `origin` should be familiar to every Git user. Parallelto the `master` branch, another branch exists called `develop`.

We consider `origin/master` to be the main branch where the source code of`HEAD` always reflects a *production-ready* state.

We consider `origin/develop` to be the main branch where the source code of`HEAD` always reflects a state with the latest delivered development changesfor the next release. Some would call this the “integration branch”.  This iswhere any automatic nightly builds are built from.

When the source code in the `develop` branch reaches a stable point and isready to be released, all of the changes should be merged back into `master`somehow and then tagged with a release number. How this is done in detail willbe discussed further on.

Therefore, each time when changes are merged back into `master`, this is a newproduction release *by definition*. We tend to be very strict at this, so thattheoretically, we could use a Git hook script to automatically build androll-out our software to our production servers everytime there was a commit on`master`.

## Supporting branches 

Next to the main branches `master` and `develop`, our development model usesa variety of supporting branches to aid parallel development between teammembers, ease tracking of features, prepare for production releases and toassist in quickly fixing live production problems. Unlike the main branches,these branches always have a limited life time, since they will be removedeventually.

The different types of branches we may use are:

- Feature branches
- Release branches
- Hotfix branches

Each of these branches have a specific purpose and are bound to strict rules asto which branches may be their originating branch and which branches must betheir merge targets. We will walk through them in a minute.

By no means are these branches “special” from a technical perspective.  Thebranch types are categorized by how we *use* them. They are of course plain oldGit branches.

### Feature branches 

![img](http://nvie.com/img/fb@2x.png)

- May branch off from:

  `develop`  

- Must merge back into:

  `develop`  

- Branch naming convention:

  anything except `master`, `develop`, `release-*`, or `hotfix-*`

Feature branches (or sometimes called topic branches) are used to develop newfeatures for the upcoming or a distant future release. When startingdevelopment of a feature, the target release in which this feature will beincorporated may well be unknown at that point. The essence of a feature branchis that it exists as long as the feature is in development, but will eventuallybe merged back into `develop` (to definitely add the new feature to theupcoming release) or discarded (in case of a disappointing experiment).

Feature branches typically exist in developer repos only, not in `origin`.

#### Creating a feature branch 

When starting work on a new feature, branch off from the `develop` branch.

```
$ git checkout -b myfeature develop
Switched to a new branch "myfeature"

```

#### Incorporating a finished feature on develop 

Finished features may be merged into the `develop` branch to definitely addthem to the upcoming release:

```
$ git checkout develop
Switched to branch 'develop'
$ git merge --no-ff myfeature
Updating ea1b82a..05e9557
(Summary of changes)
$ git branch -d myfeature
Deleted branch myfeature (was 05e9557).
$ git push origin develop

```

The `--no-ff` flag causes the merge to always create a new commit object, evenif the merge could be performed with a fast-forward. This avoids losinginformation about the historical existence of a feature branch and groupstogether all commits that together added the feature. Compare:

![img](http://nvie.com/img/merge-without-ff@2x.png)

In the latter case, it is impossible to see from the Git history which of thecommit objects together have implemented a feature—you would have to manuallyread all the log messages. Reverting a whole feature (i.e. a group of commits),is a true headache in the latter situation, whereas it is easily done if the`--no-ff` flag was used.

Yes, it will create a few more (empty) commit objects, but the gain is muchbigger than the cost.

### Release branches 

- May branch off from:

  `develop`

- Must merge back into:

  `develop` and `master`

- Branch naming convention:

  `release-*`

Release branches support preparation of a new production release. They allowfor last-minute dotting of i’s and crossing t’s. Furthermore, they allow forminor bug fixes and preparing meta-data for a release (version number, builddates, etc.). By doing all of this work on a release branch, the `develop`branch is cleared to receive features for the next big release.

The key moment to branch off a new release branch from `develop` is whendevelop (almost) reflects the desired state of the new release. At least allfeatures that are targeted for the release-to-be-built must be merged in to`develop` at this point in time. All features targeted at future releases maynot—they must wait until after the release branch is branched off.

It is exactly at the start of a release branch that the upcoming release getsassigned a version number—not any earlier. Up until that moment, the `develop`branch reflected changes for the “next release”, but it is unclear whether that“next release” will eventually become 0.3 or 1.0, until the release branch isstarted. That decision is made on the start of the release branch and iscarried out by the project’s rules on version number bumping.

#### Creating a release branch 

Release branches are created from the `develop` branch. For example, sayversion 1.1.5 is the current production release and we have a big releasecoming up. The state of `develop` is ready for the “next release” and we havedecided that this will become version 1.2 (rather than 1.1.6 or 2.0). So webranch off and give the release branch a name reflecting the new versionnumber:

```
$ git checkout -b release-1.2 develop
Switched to a new branch "release-1.2"
$ ./bump-version.sh 1.2
Files modified successfully, version bumped to 1.2.
$ git commit -a -m "Bumped version number to 1.2"
[release-1.2 74d9424] Bumped version number to 1.2
1 files changed, 1 insertions(+), 1 deletions(-)

```

After creating a new branch and switching to it, we bump the version number.Here, `bump-version.sh` is a fictional shell script that changes some files inthe working copy to reflect the new version. (This can of course be a manualchange—the point being that *some* files change.) Then, the bumped versionnumber is committed.

This new branch may exist there for a while, until the release may be rolledout definitely. During that time, bug fixes may be applied in this branch(rather than on the `develop` branch). Adding large new features here isstrictly prohibited. They must be merged into `develop`, and therefore, waitfor the next big release.

#### Finishing a release branch 

When the state of the release branch is ready to become a real release, someactions need to be carried out. First, the release branch is merged into`master` (since every commit on `master` is a new release *by definition*,remember). Next, that commit on `master` must be tagged for easy futurereference to this historical version. Finally, the changes made on the releasebranch need to be merged back into `develop`, so that future releases alsocontain these bug fixes.

The first two steps in Git:

```
$ git checkout master
Switched to branch 'master'
$ git merge --no-ff release-1.2
Merge made by recursive.
(Summary of changes)
$ git tag -a 1.2

```

The release is now done, and tagged for future reference.  

> **Edit:** You might as well want to use the `-s` or `-u <key>` flags to signyour tag cryptographically.

To keep the changes made in the release branch, we need to merge those backinto `develop`, though. In Git:

```
$ git checkout develop
Switched to branch 'develop'
$ git merge --no-ff release-1.2
Merge made by recursive.
(Summary of changes)

```

This step may well lead to a merge conflict (probably even, since we havechanged the version number). If so, fix it and commit.

Now we are really done and the release branch may be removed, since we don’tneed it anymore:

```
$ git branch -d release-1.2
Deleted branch release-1.2 (was ff452fe).

```

### Hotfix branches 

![img](http://nvie.com/img/hotfix-branches@2x.png)

- May branch off from:

  `master`

- Must merge back into:

  `develop` and `master`

- Branch naming convention:

  `hotfix-*`

Hotfix branches are very much like release branches in that they are also meantto prepare for a new production release, albeit unplanned. They arise from thenecessity to act immediately upon an undesired state of a live productionversion. When a critical bug in a production version must be resolvedimmediately, a hotfix branch may be branched off from the corresponding tag onthe master branch that marks the production version.

The essence is that work of team members (on the `develop` branch) cancontinue, while another person is preparing a quick production fix.

#### Creating the hotfix branch 

Hotfix branches are created from the `master` branch. For example, say version1.2 is the current production release running live and causing troubles due toa severe bug. But changes on `develop` are yet unstable. We may then branch offa hotfix branch and start fixing the problem:

```
$ git checkout -b hotfix-1.2.1 master
Switched to a new branch "hotfix-1.2.1"
$ ./bump-version.sh 1.2.1
Files modified successfully, version bumped to 1.2.1.
$ git commit -a -m "Bumped version number to 1.2.1"
[hotfix-1.2.1 41e61bb] Bumped version number to 1.2.1
1 files changed, 1 insertions(+), 1 deletions(-)

```

Don’t forget to bump the version number after branching off!

Then, fix the bug and commit the fix in one or more separate commits.

```
$ git commit -m "Fixed severe production problem"
[hotfix-1.2.1 abbe5d6] Fixed severe production problem
5 files changed, 32 insertions(+), 17 deletions(-)

```

**Finishing a hotfix branch**

When finished, the bugfix needs to be merged back into `master`, but also needsto be merged back into `develop`, in order to safeguard that the bugfix isincluded in the next release as well. This is completely similar to how releasebranches are finished.

First, update `master` and tag the release.

```
$ git checkout master
Switched to branch 'master'
$ git merge --no-ff hotfix-1.2.1
Merge made by recursive.
(Summary of changes)
$ git tag -a 1.2.1

```

**Edit:** You might as well want to use the `-s` or `-u <key>` flags to signyour tag cryptographically.

Next, include the bugfix in `develop`, too:

```
$ git checkout develop
Switched to branch 'develop'
$ git merge --no-ff hotfix-1.2.1
Merge made by recursive.
(Summary of changes)

```

The one exception to the rule here is that, **when a release branch currentlyexists, the hotfix changes need to be merged into that release branch, insteadof develop**. Back-merging the bugfix into the release branch will eventuallyresult in the bugfix being merged into `develop` too, when the release branchis finished. (If work in `develop` immediately requires this bugfix and cannotwait for the release branch to be finished, you may safely merge the bugfixinto `develop` now already as well.)

Finally, remove the temporary branch:

```
$ git branch -d hotfix-1.2.1
Deleted branch hotfix-1.2.1 (was abbe5d6).

```

## Summary 

While there is nothing really shocking new to this branching model, the “bigpicture” figure that this post began with has turned out to be tremendouslyuseful in our projects. It forms an elegant mental model that is easy tocomprehend and allows team members to develop a shared understanding of thebranching and releasing processes.

A high-quality PDF version of the figure is provided here. Go ahead and hang iton the wall for quick reference at any time.

**Update:** And for anyone who requested it: here’s the[gitflow-model.src.key](http://github.com/downloads/nvie/gitflow/Git-branching-model-src.key.zip) of the main diagram image (Apple Keynote).



If you want to get in touch, I'm [@nvie](http://twitter.com/nvie) on Twitter.



