import subprocess
Import("env")

def get_git_version():
    try:
        # Get git tag
        tag = subprocess.check_output(['git', 'describe', '--tags', '--always', '--dirty']).decode('utf-8').strip()
        return tag
    except:
        return "unknown"

def get_git_commit():
    try:
        commit = subprocess.check_output(['git', 'rev-parse', '--short', 'HEAD']).decode('utf-8').strip()
        return commit
    except:
        return "unknown"

def get_git_branch():
    try:
        branch = subprocess.check_output(['git', 'rev-parse', '--abbrev-ref', 'HEAD']).decode('utf-8').strip()
        return branch
    except:
        return "unknown"

git_version = get_git_version()
git_commit = get_git_commit()
git_branch = get_git_branch()

print(f"Building version: {git_version} ({git_commit} on {git_branch})")

env.Append(CPPDEFINES=[
    ("GIT_VERSION", f'\\\"{git_version}\\\"'),
    ("GIT_COMMIT", f'\\\"{git_commit}\\\"'),
    ("GIT_BRANCH", f'\\\"{git_branch}\\\"'),
])