cp -R * ../$1_
cd ../$1_ && git add -A && git commit -m"---HistoryUpdated---" && git push
