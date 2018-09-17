Shanti Sarvaka JIRA Collector Block
====================================

A very simple module that nserts the Atlassian code to create a JIRA collector.
The code is from the Shanti MANU project > Administration > Issue Collector page at:
https://issues.shanti.virginia.edu/secure/ViewCollector!default.jspa?projectKey=MANU&collectorId=3b82b030

The code to implement the collector is set simply by adding a javascript call to each page. 
In the first version of this module, it was done as a block, but on revisiting it, there is no need for a block.
The position of the link is determined by the settings of the issue collecton. So the code is now 
included in the modules init() function.

There are two ways to include the code in the page as provided by Atlassian. It can be as a 
<script> tag or as a jQuery function call. The desired method is chosen through the module's
settings page.

The <script> tag is:

<script type="text/javascript" src="https://issues.shanti.virginia.edu/s/d41d8cd98f00b204e9800998ecf8427e/en_USr653vo-1988229788/6260/4/1.4.7/_/download/batch/com.atlassian.jira.collector.plugin.jira-issue-collector-plugin:issuecollector/com.atlassian.jira.collector.plugin.jira-issue-collector-plugin:issuecollector.js?collectorId=3b82b030"></script>

While the jQuery, or embedded Javascript, code is:

    // Requires jQuery!
    jQuery.ajax({
        url: "https://issues.shanti.virginia.edu/s/d41d8cd98f00b204e9800998ecf8427e/en_USr653vo-1988229788/6260/4/1.4.7/_/download/batch/com.atlassian.jira.collector.plugin.jira-issue-collector-plugin:issuecollector-embededjs/com.atlassian.jira.collector.plugin.jira-issue-collector-plugin:issuecollector-embededjs.js?collectorId=3b82b030",
        type: "get",
        cache: true,
        dataType: "script"
    });

This code was taken from https://issues.shanti.virginia.edu/secure/ViewCollector!default.jspa?projectKey=MANU&collectorId=3b82b030
on Mar. 23, 2017.



