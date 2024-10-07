# ---
# jupyter:
#   jupytext:
#     text_representation:
#       extension: .py
#       format_name: light
#       format_version: '1.5'
#       jupytext_version: 1.15.1
#   kernelspec:
#     display_name: Python 3 (ipykernel)
#     language: python
#     name: python3
# ---

# + [code] deletable=false editable=false
# import and initialize otter
import otter
grader = otter.Notebook("p3.ipynb")

# + editable=false
import public_tests

# +
# PLEASE FILL IN THE DETAILS
# enter none if you don't have a project partner
# you will have to add your partner as a group member on Gradescope even after you fill this

# project: p3
# submitter: sheberlein
# partner: emanter
# hours: 1

# + [markdown] deletable=false editable=false
# # Project 3: City of Madison Budget

# + [markdown] deletable=false editable=false
# ## Learning Objectives:
#
# In this project you will demonstrate your ability to:
# - import a module and use its functions,
# - write functions,
# - use default arguments when calling functions,
# - use positional and keyword arguments when calling functions,
# - avoid hardcoding, and
# - work with the index of a row of data.

# + [markdown] deletable=false editable=false
# ## Testing your code:
#
# Along with this notebook, you must have downloaded the file `public_tests.py`. If you are curious about how we test your code, you can explore this file, and specifically the function `get_expected_json`, to understand the expected answers to the questions. You can have a look at [P2](https://git.doit.wisc.edu/cdis/cs/courses/cs220/cs220-f23-projects/-/tree/main/p2) if you have forgotten how to read the outputs of the `grader.check(...)` function calls.

# + [markdown] deletable=false editable=false
# **Please go through [Lab-P3](https://git.doit.wisc.edu/cdis/cs/courses/cs220/cs220-f23-projects/-/tree/main/lab-p3) before starting this project.** The lab introduces some useful techniques necessary for this project.

# + [markdown] deletable=false editable=false
# ## Project Description:
#
# In this project, you'll analyze the yearly budgets of seven different government agencies under the control of the City of Madison. The dataset we will analyze is obtained from [the City of Madison](https://www.cityofmadison.com/finance/budget) published by the Finance Department. In this project, we will be analyzing the **Adopted Budget** of a select few agencies between the years **2019** and **2023** (both years included). You'll get practice calling functions from the `project` module, which we've provided, and practice writing your own functions.
#
# If you haven't already downloaded `project.py`, `public_tests.py`, and  `madison_budget.csv` (you can verify by running `ls` in a new terminal tab from your `p3` project directory). , please terminate the current `jupyter notebook` session, download all the required files, launch a `jupyter notebook` session again and click on *Kernel* > *Restart and Clear Output*. Start by executing all the cells (including the ones containing `import` statements).
#
# We won't explain how to use the `project` module here (i.e., the code in the `project.py` file).  Refer to [Lab-P3](https://git.doit.wisc.edu/cdis/cs/courses/cs220/cs220-f23-projects/-/tree/main/lab-p3) to understand how the inspection process works and use the `help` function to learn about the various functions inside `project.py`. Feel free to take a look at the `project.py` code, if you are curious about how it works.
#
# This project consists of writing code to answer 20 questions.

# + [markdown] deletable=false editable=false
# ## Dataset:
#
# The dataset you will be working with for this project is reproduced here:
#
# |id|agency|2019|2020|2021|2022|2023|
# |--|------|----|----|----|----|----|
# |5|Finance|4.160221|4.175833|3.744979|4.159134|4.645472|
# |19|Library|17.703565|19.163603|18.849564|19.066904|19.770825|
# |20|Fire|52.853057|57.020341|61.180396|63.742785|68.098376|
# |21|Police|76.748435|81.830699|82.794221|83.995148|86.917117|
# |23|Public Health|5.384683|6.233474|6.937629|7.489070|9.656299|
# |25|Parks|14.236916|14.736923|15.585153|15.535002|16.007257|
# |27|Metro Transit|14.211148|8.552649|8.511315|9.126564|2.009664|
#
#
# This table lists seven different government agencies, and the budgets allotted to each of these agencies (in units of millions of dollars) between the years 2019 and 2023 (inclusive of both years).
#
# The dataset is in the `madison_budget.csv` file which you downloaded. Alternatively, you can open the `madison_budget.csv` file, to look at the same data and verify answers to simple questions.

# + [markdown] deletable=false editable=false
# ## Project Requirements:
#
# You **may not** hardcode indices in your code. For example, if we ask what the budget of the *Fire* department was, in *2019*, you **must** obtain the answer with this code: `get_budget(get_id("Fire"), 2019)`.  If you **do not** use `get_id` and instead use `get_budget(20, 2019)`, the Gradescope autograder will **deduct** points.
#
# For some of the questions, we'll ask you to write (then use) a function to compute the answer. If you compute the answer **without** creating the function we ask you to write, or answer these questions without using the function, the Gradescope autograder will **deduct** points, even if your answer is correct.
#
# Students are only allowed to use Python commands and concepts that have been taught in the course before the release of P3. In particular, you are **NOT** allowed to use conditionals or iteration on this project. The Gradescope autograder will **deduct** points if you use these concepts.
#
# For more details on what will cause you to lose points during code review, please take a look at the [Grading rubric](https://git.doit.wisc.edu/cdis/cs/courses/cs220/cs220-f23-projects/-/blob/main/p3/rubric.md).

# + [markdown] deletable=false editable=false
# ## Incremental Coding and Testing:
#
# You should always strive to do incremental coding. Incremental coding enables you to avoid challenging bugs. Always write a few lines of code and then test those lines of code, before proceeding to write further code. You can call the `print` function to test intermediate step outputs. **Store your final answer for each question in the variable recommended for each question.** This step is important because Otter grades your work by comparing the value of this variable against the correct answer. So, if you store your answer in a different variable, you will not get points for it.
#
# We also recommend you do incremental testing: make sure to run the local tests as soon as you are done with a question. This will ensure that you haven't made a big mistake that might potentially impact the rest of your project solution. Please refrain from making multiple submissions on Gradescope for testing individual questions' answers. Instead use the local tests, to test your solution on your laptop. 
#
# That said, it is very **important** that you check the *Gradescope* test results as soon as you submit your project on Gradescope. Test results on *Gradescope* are typically available somewhere between 10 to 15 minutes after the submission.

# + [markdown] deletable=false editable=false
# ## Project Questions and Functions:
# -

# include the relevant import statements in this cell
import project

# +
# call the init function to load the dataset
project.init("madison_budget.csv")

# you may call the dump function here to test if you have loaded the dataset correctly.
project.dump()

# + [markdown] deletable=false editable=false
# **Question 1:** What is the `id` of the agency *Public Health*?

# +
# replace the ... with your code
# INCORRECT METHOD public_health_id = 23 => this is considered hardcoding
public_health_id = project.get_id("Public Health")

public_health_id

# + deletable=false editable=false
grader.check("q1")

# + [markdown] deletable=false editable=false
# Instead of repeatedly calling `project.get_id` function for each question, you could make these calls once at the beginning of your notebook and save the results in variables. Recall that calling the same function multiple times with the same argument(s) is a waste of computation. Complete the code in the below cell and make sure to use the relevant ID variables for the rest of the project questions.

# +
finance_id = project.get_id('Finance') # we have done this for you

# replace the ... in the line below with code to get the id of 'Library'
library_id = project.get_id("Library")

# invoke get_id for the other agencies and store the result into similar variable names

# considering that you already invokved get_id for Public Health, you need to 
# make 4 more function calls to store the ID for the rest of the agencies
fire_id = project.get_id("Fire")
metro_transit_id = project.get_id("Metro Transit")
parks_id = project.get_id("Parks")
police_id = project.get_id("Police")


# + [markdown] deletable=false editable=false
# **Question 2:** What was the budget of the agency *Finance* in *2019*?
#
# Your answer should just be a number (without any units at the end), that represents the budget of the agency in millions of dollars.
#
# You **must not** hardcode the ID of the agency. You **must** use the variable that you used to store the ID of *Finance* (assuming you already invoked `get_id` for all the agencies in the cell right below Question 1).

# +
# replace the ... with your code
finance_budget_2019 = project.get_budget(finance_id, 2019)

finance_budget_2019

# + deletable=false editable=false
grader.check("q2")


# + [markdown] deletable=false editable=false
# ### Function 1: `year_max(year)`
#
# This function will compute the **maximum** budget for any one agency in a given `year`.
#
# It has already been written for you, so you do not have to modify it. You can directly call this function to answer the following questions. 
# -

def year_max(year):
    """
    year_max(year) computes the maximum budget
    for any agency in the given year
    """
    # get the budget of each agency in the given year
    finance_budget = project.get_budget(project.get_id('Finance'), year)
    library_budget = project.get_budget(project.get_id('Library'), year)
    fire_budget = project.get_budget(project.get_id('Fire'), year)
    police_budget = project.get_budget(project.get_id('Police'), year)
    public_health_budget = project.get_budget(project.get_id('Public Health'), year)
    parks_budget = project.get_budget(project.get_id('Parks'), year)
    metro_transit_budget = project.get_budget(project.get_id('Metro Transit'), year)

    # use the built-in max function to get the maximum of the seven values
    return max(finance_budget, library_budget, fire_budget, police_budget, public_health_budget, parks_budget, metro_transit_budget)


# + [markdown] deletable=false editable=false
# **Question 3:** What was the highest budget for *any* agency in the year *2023*?
#
# You **must** call the `year_max` function to answer this question.

# +
# replace the ... with your code
max_budget_2023 = year_max(2023)

max_budget_2023

# + deletable=false editable=false
grader.check("q3")

# + [markdown] deletable=false editable=false
# **Question 4:** What was the highest budget for *any* agency in a single year in the period *2020-2022* (both years included)?
#
# Recall that we can use the `max` function to compute the maximum of some values. Look at the examples in Lab-P3 where you used the `max` function or the `year_max` function definition. To be clear, the answer to this question is a single floating point number whose value is the highest budget allotted to an agency in a single year during these three years. 
#
# You **must** invoke the `year_max` function in your answer to this question.

# +
# replace the ... with your code
max_budget_2020 = year_max(2020)
max_budget_2021 = year_max(2021)
max_budget_2022 = year_max(2022)

max_budget_2020_to_2022 = max(max_budget_2020, max_budget_2021, max_budget_2022)

max_budget_2020_to_2022

# + deletable=false editable=false
grader.check("q4")


# + [markdown] deletable=false editable=false
# ### Function 2: `agency_min(agency)`
#
# This function **must** compute the **lowest** budget allotted to the given `agency` during any year in the dataset (*2019-2023*).
#
# We'll help you get started with this function, but you need to fill in the rest of the function yourself.
# -

def agency_min(agency):
    """
    agency_min(agency) computes the lowest budget allotted
    to the given `agency` in any year
    """
    agency_id = project.get_id(agency)    
    budget_2019 = project.get_budget(agency_id, 2019)
    budget_2020 = project.get_budget(agency_id, 2020)
    # get the budgets from other years
    budget_2021 = project.get_budget(agency_id, 2021)
    budget_2022 = project.get_budget(agency_id, 2022)
    budget_2023 = project.get_budget(agency_id, 2023)
    
    # use the built-in min function (similar to the max function) to get the minimum across the 
    # five years and return that value
    
    min_budget_2019_to_2023 = min(budget_2019, budget_2020, budget_2021, budget_2022, budget_2023)
    return min_budget_2019_to_2023


# + deletable=false editable=false
grader.check("agency_min")

# + [markdown] deletable=false editable=false
# **Question 5:** What was the lowest budget allotted to the agency *Library* in a *single* year?
#
# You **must** call the `agency_min` function to answer this question.

# +
# replace the ... with your code
min_budget_library = agency_min("Library")

min_budget_library

# + deletable=false editable=false
grader.check("q5")

# + [markdown] deletable=false editable=false
# **Question 6:** What was the least budget allotted in any *single* year between the agencies *Fire*, and *Police*?
#
# Recall that we can use the `min` function to compute the minimum of some values. To be clear, the answer to this question is a single floating point number whose value is the lowest budget allotted during a single year during this entire period between *2019-2023* to any of the 2 agencies mentioned.
#
# You **must** invoke the `agency_min` function in your answer to this question.
# -

# compute and store the answer in the variable 'min_budget_fire_police'
min_budget_fire_police = min(agency_min("Fire"), agency_min("Police"))
# display the variable 'min_budget_fire_police' here
min_budget_fire_police

# + deletable=false editable=false
grader.check("q6")


# + [markdown] deletable=false editable=false
# ### Function 3: `agency_avg(agency) `
#
# This function must compute the **average** budget for the given `agency` across the five years in the dataset (i.e. *2019 - 2023*).
#
# **Hint:** start by copy/pasting the `agency_min` function definition, and renaming your copy to `agency_avg` (this is **not necessary**, but it will save you time).  
# Instead of returning the minimum of `budget_2019`, `budget_2020`, etc., return the **average** of these by adding them together, then dividing by five. 
# **You may hardcode the number 5 for this computation**.
#
# The type of the *return value* **must** be `float`.
# -

# define the function 'agency_avg' here
def agency_avg(agency):
    agency_id = project.get_id(agency)    
    budget_2019 = project.get_budget(agency_id, 2019)
    budget_2020 = project.get_budget(agency_id, 2020)
    # get the budgets from other years
    budget_2021 = project.get_budget(agency_id, 2021)
    budget_2022 = project.get_budget(agency_id, 2022)
    budget_2023 = project.get_budget(agency_id, 2023)
    
    avg_budget_2019_to_2023 = (budget_2019 + budget_2020 + budget_2021 + budget_2022 + budget_2023) / 5
    return avg_budget_2019_to_2023


# + deletable=false editable=false
grader.check("agency_avg")

# + [markdown] deletable=false editable=false
# **Question 7:** What was the average budget of the agency *Parks* between *2019* and *2023*?
#
# You **must** call the `agency_avg` function to answer this question.

# +
# compute and store the answer in the variable 'parks_avg_budget'
parks_avg_budget = agency_avg("Parks")

# display the variable 'parks_avg_budget' here
parks_avg_budget

# + deletable=false editable=false
grader.check("q7")

# + [markdown] deletable=false editable=false
# **Question 8:** What was the average budget of the agency *Public Health* between *2019* and *2023*?
#
# You **must** call the `agency_avg` function to answer this question.

# +
# compute and store the answer in the variable 'public_health_avg_budget'
public_health_avg_budget = agency_avg("Public Health")

# display the variable 'public_health_avg_budget' here
public_health_avg_budget

# + deletable=false editable=false
grader.check("q8")

# + [markdown] deletable=false editable=false
# **Question 9:** Relative to its **average**, how much **higher** or **lower** was the budget of the agency *Public Health* in *2023*?
#
# **Hint:** Compute the difference between the **average** budget and the budget in *2023* of *Public Health*. Your answer must be a **positive** number if the budget was **higher** in *2018* than on average. Your answer must be a **negative** number if the budget was **lower** in *2023* than on average.

# +
# compute and store the answer in the variable 'diff_public_health_2023_to_average'.
# it is recommended that you create more intermediary variables to make your code easier to write and read.
# some useful intermediary variables you could use/create are: 'public_health_id', 'public_health_avg_budget', and
#                                                              'public_health_budget_2023'.
public_health_budget_2023 = project.get_budget(public_health_id, 2023)

diff_public_health_2023_to_average = public_health_budget_2023 - public_health_avg_budget

# display the variable 'diff_public_health_2023_to_average' here
diff_public_health_2023_to_average

# + deletable=false editable=false
grader.check("q9")


# + [markdown] deletable=false editable=false
# ### Function 4: `year_budget(year)`
#
# This function must compute the **total** budget across all agencies for the given `year`.
#
# You can start from the following code snippet:
# -

def year_budget(year=2023): # DO NOT EDIT THIS LINE
    """
    year_budget(year) computes the total budget
    across all agencies for the given year
    """
    
    # finish this function definition and return the total budget
    # across all agencies for the given `year`
    finance_budget = project.get_budget(finance_id, year)
    fire_budget = project.get_budget(fire_id, year)
    library_budget = project.get_budget(library_id, year)
    metro_transit_budget = project.get_budget(metro_transit_id, year)
    parks_budget = project.get_budget(parks_id, year)
    police_budget = project.get_budget(police_id, year)
    public_health_budget = project.get_budget(public_health_id, year)
    return finance_budget + fire_budget + library_budget + metro_transit_budget + parks_budget + police_budget + public_health_budget
    


# + deletable=false editable=false
grader.check("year_budget")

# + [markdown] deletable=false editable=false
# **Question 10:** What was the **total** budget across all seven agencies in *2023*?
#
# You **must** call the `year_budget` function to answer this question. Use the default argument (your call to `year_sum` function **must not** pass any arguments).

# +
# compute and store the answer in the variable 'total_budget_2023'
total_budget_2023 = year_budget()

# display the variable 'total_budget_2023' here
total_budget_2023

# + deletable=false editable=false
grader.check("q10")

# + [markdown] deletable=false editable=false
# **Question 11:** What was the **total** budget across all seven agencies across the years *2019-2021* (both years included)?
#
# You **must** invoke the `year_budget` function in your answer to this question. To be clear, the answer to this question is a single floating point number whose value is the total budget across all seven agencies during these three years.

# +
# compute and store the answer in the variable 'total_budget_2019_to_2021'
total_budget_2019_to_2021 = year_budget(2019) + year_budget(2020) + year_budget(2021)

# display the variable 'total_budget_2019_to_2021' here
total_budget_2019_to_2021

# + deletable=false editable=false
grader.check("q11")


# + [markdown] deletable=false editable=false
# ### Function 5: `change_per_year(agency, start_year, end_year)`
#
# This function should return the **average increase or decrease** in budget (must be **positive** if there's an **increase**, and **negative** if there’s a **decrease**) over the period from `start_year` to `end_year` for the given `agency`.
#
# The type of the *return value* **must** be `float`.
#
# We're not asking you to do anything complicated here; you just need to compute the **difference** in budget between the end year and the start year, then **divide** by the number of elapsed years. Recall that you created a similar function in the lab. You can start with the following code snippet (with the default arguments):
# -

def change_per_year(agency, start_year=2019, end_year=2023): # DO NOT EDIT THIS LINE
    """
    change_per_year(agency, start_year, end_year) computes the average increase 
    or decrease in budget over the period from `start_year` to `end_year` for the 
    given `agency`
    """
    
    # TODO: compute and return the change per year in the budget of the agency between start_year and end_year
    # TODO: it is recommended that you create intermediary variables to make your code easier to write and read.
    # TODO: some useful intermediary variables you could create are: 
    #       'budget_start_year', 'budget_end_year', 'budget_difference'.
    budget_start_year = project.get_budget(project.get_id(agency), start_year)
    budget_end_year = project.get_budget(project.get_id(agency), end_year)
    budget_difference = budget_end_year - budget_start_year
    years_elapsed = end_year - start_year
    return budget_difference / years_elapsed
    


# + deletable=false editable=false
grader.check("change_per_year")

# + [markdown] deletable=false editable=false
# **Question 12:** How much has the budget of the agency *Police* changed per year (on average) from *2019* to *2023*?
#
# You **must** call the `change_per_year` function to answer this question. Use the default arguments (your call to `change_per_year` function **must not** pass any more arguments than is absolutely necessary).

# +
# compute and store the answer in the variable 'police_average_change'
police_average_change = change_per_year("Police")

# display the variable 'police_average_change' here
police_average_change

# + deletable=false editable=false
grader.check("q12")

# + [markdown] deletable=false editable=false
# **Question 13:** How much has the budget of the agency *Fire* changed per year (on average) from *2020* to *2023*?
#
# You **must** call the `change_per_year` function to answer this question. Use the default arguments (your call to `change_per_year` function **should not** pass any more arguments than is absolutely necessary).

# +
# compute and store the answer in the variable 'fire_average_change'
fire_average_change = change_per_year("Fire", start_year = 2020)

# display the variable 'fire_average_change' here
fire_average_change

# + deletable=false editable=false
grader.check("q13")

# + [markdown] deletable=false editable=false
# **Question 14:** How much has the budget of the agency *Finance* changed per year (on average) from *2019* to *2021*?
#
# You **must** call the `change_per_year` function to answer this question. Use the default arguments (your call to `change_per_year` function **should not** pass any more arguments than is absolutely necessary).

# +
# compute and store the answer in the variable 'finance_average_change'
finance_average_change = change_per_year("Finance", end_year = 2021)

# display the variable 'finance_average_change' here
finance_average_change

# + deletable=false editable=false
grader.check("q14")

# + [markdown] deletable=false editable=false
# **Question 15:** How much has the budget of the agency *Metro Transit* changed per year (on average) from *2020* to *2022*?
#
# You **must** call the `change_per_year` function to answer this question. Use the default arguments (your call to `change_per_year` function **should not** pass any more arguments than is absolutely necessary).

# +
# compute and store the answer in the variable 'metro_transit_average_change'
metro_transit_average_change = change_per_year("Metro Transit", 2020, 2022)

# display the variable 'metro_transit_average_change' here
metro_transit_average_change

# + deletable=false editable=false
grader.check("q15")


# + [markdown] deletable=false editable=false
# ### Function 6: `extrapolate(agency, target_year, start_year, end_year)`
#
# This function **must** compute the **average** change per year from the data from `start_year` to `end_year` for `agency`. It **must** then return the **predicted budget** in `target_year`, assuming budget continues increasing (or decreasing) by that same **constant** amount each year.
#
# The type of the *return value* **must** be `float`.
#
# You **must** define `extrapolate` so that the parameter `start_year` has the **default argument** `2019` and `end_year` has the **default argument** `2023`.
#
# You **must** call the `change_per_year` function in the definition of `extrapolate`. **Do not** manually recompute the average change in budget.
# -

# define the function extrapolate(agency, target_year, start_year, end_year) here.
# it should return the estimated budget of the `agency` in `target_year` based on the 
# average change in the budget between `start_year` and `end_year`.
# it is recommended that you create intermediary variables to make your code easier to write and read.
def extrapolate(agency, target_year, start_year = 2019, end_year = 2023):
    avg_change_in_budget = change_per_year(agency, start_year, end_year)
    end_year_budget = project.get_budget(project.get_id(agency), end_year)
    estimated_budget = (target_year - end_year) * avg_change_in_budget + end_year_budget
    return estimated_budget



# + deletable=false editable=false
grader.check("extrapolate")

# + [markdown] deletable=false editable=false
# **Question 16:** What is the **estimated** budget for the agency *Library* in *2025* based on the **average change** in budget per year for it between *2019* and *2023*?
#
# You **must** call the `extrapolate` function to answer this question. Use the default arguments if possible (your call to `extrapolate` function **must not** pass any more arguments than is absolutely necessary).

# +
# compute and store the answer in the variable 'library_budget_2025'
library_budget_2025 = extrapolate("Library", target_year = 2025)

# display the variable 'library_budget_2025' here
library_budget_2025

# + deletable=false editable=false
grader.check("q16")

# + [markdown] deletable=false editable=false
# **Question 17:** What is the **estimated budget** for the agency *Parks* in *2030* based on the **average change** in budget per year for it between *2021* and *2023*?
#
# You **must** call the `extrapolate` function to answer this question. Use the default arguments if possible (your call to `extrapolate` function **must not** pass any more arguments than is absolutely necessary).

# +
# compute and store the answer in the variable 'parks_budget_2030'
parks_budget_2030 = extrapolate("Parks", target_year = 2030, start_year = 2021)

# display the variable 'parks_budget_2030' here
parks_budget_2030

# + deletable=false editable=false
grader.check("q17")

# + [markdown] deletable=false editable=false
# **Question 18:** What is the **difference** between the **estimated budget** for the agency *Police* in *2023* based on the **average change** per year between *2019* and *2022* and the **actual** budget in *2023*?
#
# You **must** invoke the `extrapolate` function in your answer to this question. A **positive** answer implies that the actual budget in *2023* is **higher**, while a negative answer implies that it is lower. Use the default arguments if possible (your call to `extrapolate` function **must not** pass any more arguments than is absolutely necessary).

# +
# compute and store the answer in the variable 'police_diff_estimate_budget'
police_diff_estimate_budget = project.get_budget(police_id, 2023) - extrapolate("Police", target_year = 2023, end_year = 2022)

# display the variable 'police_diff_estimate_budget' here
police_diff_estimate_budget

# + deletable=false editable=false
grader.check("q18")

# + [markdown] deletable=false editable=false
# **Question 19:** What is the **difference** between the **estimated budget** for the agency *Metro Transit* in *2023* based on the **average change** per year between *2019* and *2022* and the **actual** budget in *2023*?
#
# You **must** invoke the `extrapolate` function in your answer to this question. A **positive** answer implies that the actual budget in *2023* is **higher**, while a negative answer implies that it is lower. Use the default arguments if possible (your call to `extrapolate` function **must not** pass any more arguments than is absolutely necessary).

# +
# compute and store the answer in the variable 'metro_transit_diff_estimate_budget'
metro_transit_diff_estimate_budget = project.get_budget(metro_transit_id, 2023) - extrapolate("Metro Transit", 2023, end_year = 2022)

# display the variable 'metro_transit_diff_estimate_budget' here
metro_transit_diff_estimate_budget

# + deletable=false editable=false
grader.check("q19")

# + [markdown] deletable=false editable=false
# **Question 20:** What is the **standard deviation** of the budget allotted to the agency *Metro Transit* over the five years?
#
# **Hint:** You **must** compute the *population standard deviation* as in this [example](https://en.wikipedia.org/wiki/Standard_deviation#Population_standard_deviation_of_grades_of_eight_students). **You may hardcode the number 5 for this computation**.
#
# **Hint:** You can find the square root of any number by raising it to the exponent `0.5`. In other words, the square root of `2` can be computed as `2**(0.5)`.

# +
# compute and store the answer in the variable 'metro_transit_budget_std_dev'
avg_metro_transit_budget = agency_avg("Metro Transit")
deviations = (avg_metro_transit_budget - project.get_budget(metro_transit_id, 2019))**2 + (avg_metro_transit_budget - project.get_budget(metro_transit_id, 2020))**2 + (avg_metro_transit_budget - project.get_budget(metro_transit_id, 2021))**2 + (avg_metro_transit_budget - project.get_budget(metro_transit_id, 2022))**2 + (avg_metro_transit_budget - project.get_budget(metro_transit_id, 2023))**2
variance = deviations / 5
metro_transit_budget_std_dev = variance**(0.5)

# display the variable 'metro_transit_budget_std_dev' here
metro_transit_budget_std_dev

# + deletable=false editable=false
grader.check("q20")

# + deletable=false editable=false
grader.check("general_deductions")

# + deletable=false editable=false
grader.check("summary")

# + [markdown] deletable=false editable=false
# ## Submission
# It is recommended that at this stage, you Restart and Run all Cells in your notebook.
# That will automatically save your work and generate a zip file for you to submit.
#
# **SUBMISSION INSTRUCTIONS**:
# 1. **Upload** the zipfile to Gradescope.
# 2. If you completed the project with a **partner**, make sure to **add their name** by clicking "Add Group Member"
# in Gradescope when uploading the zip file.
# 3. Check **Gradescope** results as soon as the auto-grader execution gets completed.
# 4. Your **final score** for this project is the score that you see on **Gradescope**.
# 5. You are **allowed** to resubmit on Gradescope as many times as you want to.
# 6. **Contact** a TA/PM if you lose any points on Gradescope for any **unclear reasons**.

# + [code] deletable=false editable=false
# running this cell will create a new save checkpoint for your notebook
from IPython.display import display, Javascript
display(Javascript('IPython.notebook.save_checkpoint();'))

# + [code] deletable=false editable=false
# !jupytext --to py p3.ipynb

# + [code] deletable=false editable=false
public_tests.check_file_size("p3.ipynb")
grader.export(pdf=False, run_tests=False, files=["p3.py"])

# + [markdown] deletable=false editable=false
#  
