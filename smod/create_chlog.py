#!/usr/bin/env python

import git
import time

repo = git.Repo(".")

class DebChangelogFile(object):
    def __init__(self,reppath,ptag):
        self.repo = git.Repo(reppath)
        self.head = self.__get_head()
        self.tag = self.__get_ptag(ptag)
        self.pkg_version = ""
        self.pkg_name = ""
        self.pkg_dist = ""
        self.pkg_ulevel = ""
        self.entry_header = ""

        self.eh_format = "%s (%s) %s; urgency=%s\n"
        self.eh = ""


    def __get_head(self):
        """
        __get_head(self):
        Returns the active head of the actual 
        GIT repository.
        """
        #get the active branch
        bname = self.repo.active_branch
        for h in self.repo.heads:
            if h.name ==bname:
                head = h
                break

        return head

    def __get_ptag(self,tname):
        """
        __get_ptag(self,tname):
        Returns the tag of the previous release.
        """
        #get the last tagged version
        for t in repo.tags:
            if t.name == tname:
                tag = t
                break

        return tag

    def __eh_update(self):
        ostr = self.eh_format %(self.pkg_name,self.pkg_version,self.pkg_dist,self.pkg_ulevel)

        return ostr

    def ce_footer(self,name,mail,date):
        date_format = "%a, %d %b %Y %H:%M:%S"
        date_str = time.strftime(date_format,date)

        tz_sign = "+" 
        if(time.timezone<0): tz_sign="-"
        tz_offset = abs(time.timezone)/60
        tz_offmin = tz_offset%60
        tz_offh = (tz_offset-tz_offmin)/60

        ostr = "-- %s <%s>  %s %s%02i%02i\n" %(name,mail,date_str,tz_sign,tz_offh,tz_offmin)
        return ostr

    def ce_text(self,text):
        text = text.replace("\n","\n    ")
        ostr = "  * %s\n" %text

        return ostr

    def create(self,clname):
        """
        create(clname):
        Create changelog file.
        """

        #iterate over all commits since the last version
        citer = repo.commits_between(self.tag.commit.id,self.head.commit.id)
        lc = []
        for c in citer:
            lc.append(c)

        lc.reverse()

        for c in lc:
            text = c.message
            author = c.author.name
            email = c.author.email
            date = c.committed_date
            text = ce_text(text)
            footer = ce_footer(author,email,date)
            print ce_head("libpniutils","0.1.0","unstable","low")
            print text
            print footer

    

